#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include  "esp_log.h"
#include "esp_timer.h"

#include "inc/mpu6050_iface.h"
#include "inc/pwm_iface.h"
#include "ws_server.h"

float Kp = 7;          
float Ki = 6;            
float Kd = 3;              
float iTerm = 0;      
float lastTime = 0;   
float maxPID = 255;   
float oldValue = 0;    

float targetValue = 0;

#define LOOP_TIME 10         
unsigned long timerValue = 0;

float pid(float target, float current) {

	// Calculate the time since function was last called
	float thisTime = esp_timer_get_time();
	float dT = thisTime - lastTime;
	lastTime = thisTime;

	float error = target - current;
	iTerm += error * dT; 
	float dTerm = (oldValue - current) / dT;
	oldValue = current;

	float result = (error * Kp) + (iTerm * Ki) + (dTerm * Kd);

	if (result > maxPID) result = maxPID;
	else if (result < -maxPID) result = -maxPID;

	return result;
}




static void hw_init()
{ 
	/**init ledc for pwm*/
	ledc_init();

	/*init timer*/
	 timerValue = esp_timer_get_time();

	/**init mpu6050 module*/
    mpu6050_i2c_init();
    mpu6050_init();

    // In order to get accurate calculation of complimentary angle we need fast reading (5ms)
    // FreeRTOS resolution is 10ms, so esp_timer is used
    const esp_timer_create_args_t cal_timer_config = {
        .callback = mpu6050_read,
        .arg = NULL,
        .name = "MPU6050 timer",
        .skip_unhandled_events = true, //true for versions (4, 3, 0) and above
        .dispatch_method = ESP_TIMER_TASK
    };
    esp_timer_handle_t cal_timer = NULL;
    esp_timer_create(&cal_timer_config, &cal_timer);
    esp_timer_start_periodic(cal_timer, 5000); // 5ms

	
}

/******* MAIN LOOP *********
void control_task() {
	if (esp_timer_get_time() - timerValue > LOOP_TIME) {
		timerValue = esp_timer_get_time();

		// Replace getAngle() with your sensor data reading
		float currentValue = getAngle();
		float motorOutput = pid(targetValue, currentValue);

		// Replace moveMotors() with your desired output
		moveMotors(motorOutput);
	}
}
*/
void app_main(void)
{
    static httpd_handle_t server = NULL;

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());

    /* Register event handlers to stop the server when Wi-Fi or Ethernet is disconnected,
     * and re-start it upon connection.
     */
#ifdef CONFIG_EXAMPLE_CONNECT_WIFI
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &connect_handler, &server));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, &server));
#endif // CONFIG_EXAMPLE_CONNECT_WIFI
#ifdef CONFIG_EXAMPLE_CONNECT_ETHERNET
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_ETH_GOT_IP, &connect_handler, &server));
    ESP_ERROR_CHECK(esp_event_handler_register(ETH_EVENT, ETHERNET_EVENT_DISCONNECTED, &disconnect_handler, &server));
#endif // CONFIG_EXAMPLE_CONNECT_ETHERNET

    /* Start the server for the first time */
    server = start_webserver();
}
