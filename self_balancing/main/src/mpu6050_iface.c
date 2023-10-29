
#include "../inc/mpu6050_iface.h"

static const char *TAG = "mpu5050";

static mpu6050_handle_t mpu6050_dev = NULL;

static mpu6050_acce_value_t acce;
static mpu6050_gyro_value_t gyro;
static complimentary_angle_t complimentary_angle;

esp_err_t mpu6050_i2c_init(void)
{
    const i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = BSP_I2C_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = BSP_I2C_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000
    };
    i2c_param_config(BSP_I2C_NUM, &i2c_conf);
    i2c_driver_install(BSP_I2C_NUM, i2c_conf.mode, 0, 0, 0);

    return ESP_OK;
}

void mpu6050_init()
{
    mpu6050_dev = mpu6050_create(BSP_I2C_NUM, MPU6050_I2C_ADDRESS);
    mpu6050_config(mpu6050_dev, ACCE_FS_4G, GYRO_FS_500DPS);
    mpu6050_wake_up(mpu6050_dev);
}


void mpu6050_read(void *pvParameters)
{
    mpu6050_get_acce(mpu6050_dev, &acce);
    mpu6050_get_gyro(mpu6050_dev, &gyro);
    mpu6050_complimentory_filter(mpu6050_dev, &acce, &gyro, &complimentary_angle);
}

void show_acce_data(void)
{
    ESP_LOGI(TAG, "acce_x:%.2f, acce_y:%.2f, acce_z:%.2f", acce.acce_x, acce.acce_y, acce.acce_z);
}
void show_gyro_data(void)
{
    ESP_LOGI(TAG, "gyro_x:%.2f, gyro_y:%.2f, gyro_z:%.2f", gyro.gyro_x, gyro.gyro_y, gyro.gyro_z);
}

void show_complimentary_angle(void)
{
    ESP_LOGI(TAG, "roll:%.2f, pitch:%.2f", complimentary_angle.roll, complimentary_angle.pitch);
}

