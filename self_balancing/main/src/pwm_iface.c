#include "../inc/pwm_iface.h"

void pwm(ledc_channel_t channel, uint8_t dutyCycle)
{
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_HIGH_SPEED_MODE, channel, dutyCycle));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_HIGH_SPEED_MODE, channel));
}

void ledc_init()
{
    ledc_timer_config_t ledc_timer = {
    .speed_mode       = LEDC_HIGH_SPEED_MODE,
    .timer_num        = LEDC_TIMER_0,
    .duty_resolution  = LEDC_TIMER_10_BIT,
    .freq_hz          = 1000,
    .clk_cfg          = LEDC_AUTO_CLK
};
ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

ledc_channel_config_t  ledc_channel[2]; 
ledc_channel[0].channel = LEDC_CHANNEL_0;
ledc_channel[0].gpio_num = PWM_OUT1;
ledc_channel[1].channel = LEDC_CHANNEL_1;
ledc_channel[1].gpio_num = PWM_OUT2;
for(int i = 0; i<2;i++)
{
    ledc_channel[i].speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel[i].timer_sel = LEDC_TIMER_0;
    ledc_channel[i].intr_type = LEDC_INTR_DISABLE;
    ledc_channel[i].duty = 0;
    ledc_channel[i].hpoint = 0;
        
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel[i]));
}

}

