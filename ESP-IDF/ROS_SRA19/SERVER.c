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

 
#include "SERVER.h"

//Extracts a set of characters from  a given string
char substring(char string[1000],int start, int end)        
{

   int c = 0;

   for(int i = 0 ; i < 12 ; i++)
   {
    sub[i] = "" ;
   }

   while (c < end - start - 1) 
   {
      sub[c] = string[start+c];
      c++;
   }

   return atoi(sub);

}

//Finds a particular character in a given string
int find(char array[1000], char point)
{
    return(strchr(array,point) - array + 1);
}

//Control function for Wifi initialisation and working 
esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch (event->event_id) 
    {
        case SYSTEM_EVENT_STA_START:
            esp_wifi_connect();
            ESP_LOGI(TAG, "SYSTEM_EVENT_STA_START");
            break;

        case SYSTEM_EVENT_STA_CONNECTED:
            /* enable ipv6 */
            tcpip_adapter_create_ip6_linklocal(TCPIP_ADAPTER_IF_STA);
            break;

        case SYSTEM_EVENT_STA_GOT_IP:
            xEventGroupSetBits(wifi_event_group, BIT0);
            ESP_LOGI(TAG, "SYSTEM_EVENT_STA_GOT_IP");
            break;

        case SYSTEM_EVENT_STA_DISCONNECTED:
            /* This is a workaround as ESP32 WiFi libs don't currently auto-reassociate. */
            esp_wifi_connect();
            xEventGroupClearBits(wifi_event_group, BIT0);
            // xEventGroupClearBits(wifi_event_group, BIT1);
            break;

        case SYSTEM_EVENT_AP_STA_GOT_IP6:
            xEventGroupSetBits(wifi_event_group, BIT1);
            ESP_LOGI(TAG, "SYSTEM_EVENT_STA_GOT_IP6");

            char *ip6 = ip6addr_ntoa(&event->event_info.got_ip6.ip6_info.ip);
            ESP_LOGI(TAG, "IPv6: %s", ip6);

        default:
            break;
    }
    return ESP_OK;
}

//Intialise WIFI for ESP32
void initialise_wifi_server(void)
{
    tcpip_adapter_init();
    wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    wifi_config_t wifi_config = 
    {
        .sta = 
        {
            .ssid = EXAMPLE_WIFI_SSID,
            .password = EXAMPLE_WIFI_PASS,
        },
    };
    ESP_LOGI(TAG, "Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );
}


//Connect ESP to access point
void wait_for_ip()
{
    uint32_t bits = BIT0 | BIT1 ;

    ESP_LOGI(TAG, "Waiting for AP connection...");
    xEventGroupWaitBits(wifi_event_group, bits, false, true, portMAX_DELAY);
    ESP_LOGI(TAG, "Connected to AP");
}

//Get ESP32's IP address
void ip_address()
{
    destAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(PORT);
    addr_family = AF_INET;
    ip_protocol = IPPROTO_IP;
    inet_ntoa_r(destAddr.sin_addr, addr_str, sizeof(addr_str) - 1);
}