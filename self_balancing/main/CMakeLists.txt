idf_component_register(SRCS "main.c" "src/mpu6050_iface" "src/pwm_iface"
                    INCLUDE_DIRS "inc"
                    REQUIRES "mpu6050" "ws_server" "esp_timer"
                    )
