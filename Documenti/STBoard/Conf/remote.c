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
#include <string.h>
#include <FreeRTOS.h>
#include <list.h>
#include <FreeRTOS_IP.h>
#include <FreeRTOS_sockets.h>
#include <components.h>
#include <can_lld_cfg.h>

#include <network.h>

#include <candefs.h>
#include <lindefs.h>
#include <ethdefs.h>
#include "AEK_COM_10BAST1S.h"

#define LOG_ENABLED 1

/*
 * The CAN device.
 */
#define CAN_DEVICE_REMOTE3                      CAND4
#define CAN_DEVICE_REMOTE1                      CAND2

#define CAN_SLEEP_ID_MSG                        0x7e0


#define ETH_RECV_TASK_PRIORITY          2
#define ETH_RECV_TASK_STACK_SIZE        1024

#define REMOTE_DEVICE_TASK_PRIORITY     2
#define REMOTE_DEVICE_TASK_STACK_SIZE   1024


uint8_t eth_tx_buf[ETH_HEADER_LEN + ETH_DLC_LEN + ETH_DATA_LEN];
uint8_t can_msg_sts = 0;
uint8_t can_msg_sleep = 0;


/* Ethernet socket used to send/receive data to/from gateway */
static Socket_t gateway_socket = FREERTOS_INVALID_SOCKET;

portTASK_FUNCTION(ethRecvTask, pvParam ) {

	  (void)pvParam;
	  uint8_t buf[16];
	  int32_t n;

    #if (USE_UDP == 1)
      struct freertos_sockaddr source_addr;
      socklen_t source_addr_len = sizeof(source_addr);
    #endif

	  for( ;; ) {
	    #if (USE_UDP == 1)
          n = FreeRTOS_recvfrom(gateway_socket, buf, 16, 0, &source_addr, &source_addr_len);
      #else
          n = FreeRTOS_recv(gateway_socket, buf, 16, 0);
      #endif

	    if (n > 0) {
	    } else if (n == 0) {
	    } else {
	      #if (USE_UDP == 0)
              FreeRTOS_shutdown(gateway_socket, FREERTOS_SHUT_RDWR);
              break;
        #endif
	    }
	  }

	  #if (USE_UDP == 0)
      /* Destroy this task */
      vTaskDelete(NULL);
    #endif
	}


static void eth_send_message(uint8_t *data, uint16_t len) {
  int32_t n;
  
  #if (USE_UDP == 1)
    /* UDP: Inviamo il datagramma intero a un indirizzo noto */
    struct freertos_sockaddr gateway_address;
    gateway_address.sin_port = FreeRTOS_htons(ETH_PORT);
    gateway_address.sin_addr = FreeRTOS_inet_addr(SPC5_ETH0_GATEWAY_ADDR);
    gateway_address.sin_len = sizeof(gateway_address);

    n = FreeRTOS_sendto(gateway_socket, data, len, 0, &gateway_address, sizeof(gateway_address));
    if (n < 0) {
        /* Errore UDP */
    }
  #else
    /* TCP: Ciclo stream originale */
    int32_t p = 0;
    while (len != 0) {
      n = FreeRTOS_send(gateway_socket, &data[p], len, 0);
      if (n < 0) {
        /* Error: stop sending data */
        break;
      }
      p += n;
      len -= n;
    }
  #endif
}


static int32_t eth_start_client(void) {
  int32_t ret;
  const char *pcInterfaceName = "eth1";
  ret = 1;

  #if (USE_UDP == 1)
    gateway_socket = FreeRTOS_socket(FREERTOS_AF_INET, FREERTOS_SOCK_DGRAM, FREERTOS_IPPROTO_UDP);
  #else
    gateway_socket = FreeRTOS_socket(FREERTOS_AF_INET, FREERTOS_SOCK_STREAM, FREERTOS_IPPROTO_TCP);
  #endif

  ret = FreeRTOS_setsockopt(gateway_socket, 0, FREERTOS_SO_BINDTODEVICE, pcInterfaceName, strlen(pcInterfaceName));

  if (gateway_socket != FREERTOS_INVALID_SOCKET) {
    
  #if (USE_UDP == 1)
      /* UDP: Non c'è fase di connect, avviamo direttamente il task di ricezione */
      ret = xTaskCreate(ethRecvTask, "ethRecvTask", ETH_RECV_TASK_STACK_SIZE, NULL, ETH_RECV_TASK_PRIORITY, NULL);
      ret = (ret == pdPASS) ? 0 : 1;
  #else
      /* TCP: Logica originale con connect */
      int32_t timeout;
      uint32_t address;
      struct freertos_sockaddr gateway_address;
      
      address = FreeRTOS_inet_addr(SPC5_ETH0_GATEWAY_ADDR);
      gateway_address.sin_port = FreeRTOS_htons(ETH_PORT);
      gateway_address.sin_addr = address;
      gateway_address.sin_len = sizeof(gateway_address);

      timeout = 1000000;
      do {
        taskYIELD();
        ret = FreeRTOS_connect(gateway_socket, &gateway_address, sizeof(gateway_address));
      } while ((ret != 0) && (timeout-- != 0));

      if (ret == 0) {
        ret = xTaskCreate(ethRecvTask, "ethRecvTask", ETH_RECV_TASK_STACK_SIZE, NULL, ETH_RECV_TASK_PRIORITY, NULL);
        ret = (ret == pdPASS) ? 0 : 1;
      }
  #endif

    if (ret != 0) {
      FreeRTOS_closesocket(gateway_socket);
    }
  }

  return (ret == 0) ? pdPASS : pdFAIL;
}

/*
 * CAN
 */
void SUBSYS_0_CAN1_rx_callback(uint32_t msg_buf, CANRxFrame can_msg) {
  (void)msg_buf;
  (void)can_msg;
  uint8_t i = 0;
  eth_tx_buf[0] = ETH_MSG_1;
  eth_tx_buf[1] = can_msg.DLC;
  for(i = 0; i < 8; i++){
	  eth_tx_buf[i+2] = can_msg.data8[i];
  }
  can_msg_sts = 1;
  if(can_msg.ID == CAN_SLEEP_ID_MSG){
	  can_msg_sleep = 1;
  }
}


void SUBSYS_0_CAN3_rx_callback(uint32_t msg_buf, CANRxFrame can_msg) {
  (void)msg_buf;
  (void)can_msg;
  uint8_t i = 0;
  eth_tx_buf[0] = ETH_MSG_1;
  eth_tx_buf[1] = can_msg.DLC;
  for(i = 0; i < 8; i++){
	  eth_tx_buf[i+2] = can_msg.data8[i];
  }
  can_msg_sts = 1;
  if(can_msg.ID == CAN_SLEEP_ID_MSG){
	  can_msg_sleep = 1;
  }
}


portTASK_FUNCTION(remoteDevTask, pvParam ) {
  (void)pvParam;

  int32_t eth_ok = 0;

  /* Start CAN */
  can_lld_start(&CAN_DEVICE_REMOTE3, &can_config_SUBSYS_0_CAN3);
  can_lld_start(&CAN_DEVICE_REMOTE1, &can_config_SUBSYS_0_CAN1);

  /* Start Ethernet connection */
  eth_ok = eth_start_client();

  for ( ; ; ) {

    /* Ethernet */
    if (eth_ok == pdPASS) {

    	if(can_msg_sts && can_msg_sleep == 0){
    		eth_send_message(eth_tx_buf, ETH_HEADER_LEN + ETH_DLC_LEN + ETH_DATA_LEN);
    		can_msg_sts = 0;
    	}
    	else if(can_msg_sts && can_msg_sleep == 1){
    		AEK_COM_10BASET1S_Sleep();
    		can_msg_sleep = 0;
    		can_msg_sts = 0;
    	}

    }

    vTaskDelay(500);
  }
}


uint32_t remote_start(void) {

  uint32_t ret;

  /* create remote device task */
  ret = xTaskCreate(remoteDevTask, "remoteDevTask", REMOTE_DEVICE_TASK_STACK_SIZE, NULL, REMOTE_DEVICE_TASK_PRIORITY, NULL);

  return (ret == pdPASS) ? 0 : 1;
}
