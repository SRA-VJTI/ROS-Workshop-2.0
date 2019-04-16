/*
Copyright (c) 2019, Society of Robotics and Automation, VJTI
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//Include library
#ifndef SERVER_H
#define SERVER_h

//C components
#include <string.h>
#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>

//ESP components
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>
#include "esp_attr.h"

//Motor-PWM components
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

//Define the WIFI SSID & password (Hotspot config)
#define EXAMPLE_WIFI_SSID "WIFI"
#define EXAMPLE_WIFI_PASS "PASSWORD"

//Port for type of transfer (e.g. HTTP, FTP, etc.)
#define PORT 80


static EventGroupHandle_t wifi_event_group;
static const char *TAG = "example";
char rx_buffer[128];
char addr_str[128];
char sub[12];
int addr_family;
int ip_protocol;
struct sockaddr_in destAddr;

char substring(char string[1000],int start, int end);

int find(char array[1000], char point);

esp_err_t event_handler(void *ctx, system_event_t *event);

void initialise_wifi_server(void);

void wait_for_ip();

void ip_address();

#endif