/****************************************************************************
*
* Copyright © 2018-2019 STMicroelectronics - All Rights Reserved
*
* This software is licensed under SLA0098 terms that can be found in the
* DM00779817_1_0.pdf file in the licenses directory of this software product.
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
*****************************************************************************/
#include <FreeRTOS.h>
#include <list.h>
#include <FreeRTOS_IP.h>
#include <FreeRTOS_sockets.h>

#include <ethdefs.h>
#include <gateway.h>


#define ACCEPT_TASK_PRIORITY         2
#define ACCEPT_TASK_STACK_SIZE       1024

#define ETH_SERVER_TASK_PRIORITY     2
#define ETH_SERVER_TASK_STACK_SIZE   2048

static TaskHandle_t acceptTaskHandle;

uint32_t ETHD1 = 0;

portTASK_FUNCTION(eth_server, pvParam) {

  Socket_t eth_socket;
  GatewayMsg_t gw_msg;
  uint8_t buf[GATEWAY_MSG_DATA_LEN];
  int32_t n;

  #if (USE_UDP == 1)
    struct freertos_sockaddr source_addr;
    socklen_t source_addr_len = sizeof(source_addr);
  #endif

  /* Set the gateway socket */
  ETHD1 = (uint32_t)pvParam;
  eth_socket = (Socket_t)pvParam;


  for ( ; ; ) {
    #if (USE_UDP == 1)
        n = FreeRTOS_recvfrom(eth_socket, buf, 10, 0, &source_addr, &source_addr_len);
    #else
        n = FreeRTOS_recv(eth_socket, buf, 10, 0);
    #endif

    if (n > 0) {
      /*
       * Silently failing if message length is
       * greater than gateway message data length.
       */
      if (n <= GATEWAY_MSG_DATA_LEN) {
        gw_msg.type = GATEWAY_MSG_ETH;
        gw_msg.id   = buf[0];
   	    memcpy(gw_msg.data, &buf[2], buf[1]);
   	    gw_msg.data_len = buf[1];

   	    send_to_gateway_from_task(&gw_msg);
   	  }
    } else if (n == 0) {

    } else {
      #if (USE_UDP == 0)
            FreeRTOS_shutdown(eth_socket, FREERTOS_SHUT_RDWR);
            break; 
      #endif
    }
  }

  #if (USE_UDP == 0)
    /* Destroy this task (solo TCP) */
    vTaskDelete(NULL);
  #endif
}

portTASK_FUNCTION(acceptTask, pvParam) {

  Socket_t listening_socket = (Socket_t)pvParam;
  Socket_t connected_socket;
  struct freertos_sockaddr connected_client;
  socklen_t connected_client_size = sizeof(connected_client);

  for( ; ; ) {
    /* Wait for incoming connections. */
    connected_socket = FreeRTOS_accept(listening_socket, &connected_client, &connected_client_size);

    /* Create RTOS task to handle the connection. */
    xTaskCreate(eth_server,
                "serverTask",
                ETH_SERVER_TASK_STACK_SIZE,
	            (void *) connected_socket,
                ETH_SERVER_TASK_PRIORITY,
                NULL);
  }
}

void eth_start(void) {

  struct freertos_sockaddr bindAddress;
  Socket_t listening_socket;
  static const TickType_t listening_socket_accept_timeout = portMAX_DELAY;
  const BaseType_t childSockets = 5;
  uint32_t ret;
  const char *pcInterfaceName = "eth0";

  #if (USE_UDP == 1)
    listening_socket = FreeRTOS_socket(FREERTOS_AF_INET, FREERTOS_SOCK_DGRAM, FREERTOS_IPPROTO_UDP);
  #else
    listening_socket = FreeRTOS_socket(FREERTOS_AF_INET, FREERTOS_SOCK_STREAM, FREERTOS_IPPROTO_TCP);
  #endif
  ret = FreeRTOS_setsockopt( listening_socket, 0, FREERTOS_SO_BINDTODEVICE,  pcInterfaceName, strlen(pcInterfaceName));

  /* Check the socket was created successfully. */
  if (listening_socket != FREERTOS_INVALID_SOCKET) {

    /* Set a time out so accept() will just wait for a connection. */
    #if (USE_UDP == 0)
      FreeRTOS_setsockopt(listening_socket,
                          0,
                          FREERTOS_SO_RCVTIMEO,
                          &listening_socket_accept_timeout,
                          sizeof(listening_socket_accept_timeout));
    #endif

    /* Set the listening port to ETH_PORT. */
    bindAddress.sin_port = FreeRTOS_htons(ETH_PORT);

    if (FreeRTOS_bind(listening_socket, &bindAddress, sizeof(&bindAddress)) != 0) {
      FreeRTOS_closesocket(listening_socket);
    } else {
      #if (USE_UDP == 1)
            /* UDP: Avvia direttamente il server, niente listen/accept */
            ret = xTaskCreate(eth_server, "serverTask", ETH_SERVER_TASK_STACK_SIZE, (void *) listening_socket, ETH_SERVER_TASK_PRIORITY, NULL);
            if (ret != pdPASS) {
                FreeRTOS_closesocket(listening_socket);
            }
      #else
            /* TCP: Usa listen e avvia il task per accettare le connessioni */
            FreeRTOS_listen(listening_socket, childSockets);
            ret = xTaskCreate(acceptTask, "acceptTask", ACCEPT_TASK_STACK_SIZE, (void *) listening_socket, ACCEPT_TASK_PRIORITY, &acceptTaskHandle);
            if (ret != pdPASS) {
                FreeRTOS_closesocket(listening_socket);
            }
      #endif
    }
  }
}


void send_to_eth(void *device, uint8_t msg_id, uint8_t *buffer, uint16_t len) {
  int32_t n = 0;
  char data[20];
  Socket_t eth_socket = *((Socket_t *)device);


  if (eth_socket != FREERTOS_INVALID_SOCKET) {
    data[0] = msg_id;
    memcpy(&data[1], buffer, len);
    len++;

    #if (USE_UDP == 1)
      struct freertos_sockaddr dest_addr;
      dest_addr.sin_port = FreeRTOS_htons(ETH_PORT);
      dest_addr.sin_addr = FreeRTOS_inet_addr(DESTINATION_IP_ADDR);
      n = FreeRTOS_sendto(eth_socket, data, len, 0, &dest_addr, sizeof(dest_addr));
      
      if (n < 0) {
        /* error to handle */
      }

    #else
      while (n < len) {
        n = FreeRTOS_send(eth_socket, &data[n], len - n, 0);
        if (n < 0) {
          /* Error: stop sending data */
          break;
        }
      }
    }
}
