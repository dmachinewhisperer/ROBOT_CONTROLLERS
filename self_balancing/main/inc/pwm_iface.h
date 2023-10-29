#ifndef PWM_IFACE_H_
#define PWM_IFACE_H_

#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include  "esp_log.h"


#define PWM_OUT1 GPIO_NUM_12
#define PWM_OUT2 GPIO_NUM_13

void pwm(ledc_channel_t channel, uint8_t dutyCycle);

void ledc_init();

#endif