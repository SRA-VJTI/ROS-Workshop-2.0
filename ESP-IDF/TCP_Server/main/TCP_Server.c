#include "SERVER.h"

void tcp_server_task(void *pvParameters)
{
    while (1) 
    {

		ip_address();

        //creates an unbound socket viz. endpoint for communication
        int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
        
        if (listen_sock < 0) 
        {
            printf("Unable to create socket: errno %d\n", errno);
            break;
        }
        printf("Socket created\n");

        //assign the socket a port and and an address
        int err = bind(listen_sock, (struct sockaddr *)&destAddr, sizeof(destAddr));
        if (err != 0) 
        {
            printf("Socket unable to bind: errno %d\n", errno);
            break;
        }
        printf("Socket binded\n");

        //listen to available connections and limit them to a number
        err = listen(listen_sock, 1);
        if (err != 0) 
        {
            printf("Error occured during listen: errno %d\n", errno);
            break;
        }
        printf("Socket listening\n");


        struct sockaddr_in6 sourceAddr; // Large enough for both IPv4 or IPv6
        uint addrLen = sizeof(sourceAddr);

        //accept the first connection from listen
        int sock = accept(listen_sock, (struct sockaddr *)&sourceAddr, &addrLen);
        if (sock < 0) {
            printf("Unable to accept connection: errno %d\n", errno);
            break;
        }
        printf("Socket accepted\n");

        while (1) 
        {
        	//receive data from client
            int len = recv(sock, rx_buffer, sizeof(rx_buffer) , 0);
           
            // Error occured during receiving
            if (len <= 0) 
            {
                printf("recv failed: errno %d\n", errno);
                break;
            }
           
            // Data received
            else 
            {
                // Get the sender's ip address as string
                inet_ntoa_r(((struct sockaddr_in *)&sourceAddr)->sin_addr.s_addr, addr_str, sizeof(addr_str) - 1);

                
                
                //send back the message for error-checking
                int err = send(sock, rx_buffer, len, 0);
                if(err < 0) 
                {
                    printf("Error occured during sending: errno %d\n", errno);
                    break;

                }

                printf("%s", rx_buffer);
                printf("Received %d bytes from %s:\n", len, addr_str);
                
            }
        }

        if (sock != -1)
        {
            printf("Shutting down socket and restarting...\n");
            shutdown(sock, 0);
            close(sock);
        }
    }
    vTaskDelete(NULL);
}


void app_main()
{
    ESP_ERROR_CHECK(nvs_flash_init());
    nvs_flash_init();
    initialise_wifi_server();
    wait_for_ip();

    xTaskCreate(tcp_server_task, "tcp_server", 4096, NULL, 5, NULL);
}
