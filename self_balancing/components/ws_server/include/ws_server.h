#ifndef WS_SERVER_H_
#define WS_SERVER_H_

#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "esp_netif.h"
#include "esp_eth.h"
#include "protocol_examples_common.h"

#include <esp_http_server.h>

httpd_handle_t start_webserver(void);

esp_err_t stop_webserver(httpd_handle_t server);

void disconnect_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data);

void connect_handler(void* arg, esp_event_base_t event_base,
                            int32_t event_id, void* event_data);                               
#endif