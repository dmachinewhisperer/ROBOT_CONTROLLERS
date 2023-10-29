#ifndef MPU6050_IFACE_H_
#define MPU6050_IFACE_H_

#include <stdio.h>
#include "mpu6050.h"

#include "driver/ledc.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "driver/sdmmc_host.h"

#include "esp_log.h"
#include "esp_timer.h"

#define BSP_I2C_SCL_IO      GPIO_NUM_22
#define BSP_I2C_SDA_IO      GPIO_NUM_21
#define BSP_I2C_NUM         I2C_NUM_0
#define MPU6050_I2C_ADDRESS 0x68U


esp_err_t mpu6050_i2c_init(void);

void mpu6050_init();

void mpu6050_read(void *pvParameters);

void show_acce_data(void);

void show_gyro_data(void);

void show_complimentary_angle(void);

#endif
