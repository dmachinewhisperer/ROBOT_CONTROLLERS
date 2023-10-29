idf_component_register(
    SRCS "ws_server.c"
    INCLUDE_DIRS "include"
    REQUIRES "esp_event" "nvs_flash" "log" "esp_system" "protocol_examples_common" "esp_netif" "esp_wifi" "esp_eth" "esp_http_server"
)


set(EXTRA_COMPONENT_DIRS "$ENV{IDF_PATH}/examples/common_components/protocol_examples_common"
    )
