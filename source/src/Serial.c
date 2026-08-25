/*
 * Serial.c
 *
 *  Created on: 24 ago 2026
 *      Author: Casa
 */
#include "components.h"
#include "Serial.h"
#include "can_hal.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

extern uint8_t Handle_Req_newmsg;	// Flag per inviare il msg
extern Handle_CANFramemsg_t CAN_Msg;

uint16_t len = 0;			// Variabile per salvare la sungezza msg
uint8_t buffer[64];		// Buffer per invio messaggio su seriale		--> char e uint8_t sono uguali

/*
 * Creazione del messaggio di invio sulla seriale
 * */
void Serial_Sendmsg(char *TextType, uint32_t ID, uint8_t DLC, uint32_t *Data){
	  memset(buffer, 0, sizeof(buffer));	// Cancelliamo il buffer
	  len = 0;								// Cancelliamo il contatore
	  /* ID */
	  len += sprintf(&buffer[len], "ID=%08lX D=%d %s=", ID, DLC, TextType);
	  /* Payload */
	  switch(DLC){
	  case 1:
		  len += sprintf(&buffer[len], "%02X", Data[0]);
		  break;
	  case 2:
		  len += sprintf(&buffer[len], "%04X", Data[0]);
		  break;
	  case 3:
		  len += sprintf(&buffer[len], "%06X", Data[0]);
		  break;
	  case 4:
		  len += sprintf(&buffer[len], "%08X", Data[0]);
		  break;
	  case 5:
		  len += sprintf(&buffer[len], "%08X%02X", Data[0], Data[1]);
		  break;
	  case 6:
		  len += sprintf(&buffer[len], "%08X%04X", Data[0], Data[1]);
		  break;
	  case 7:
		  len += sprintf(&buffer[len], "%08X%06X", Data[0], Data[1]);
		  break;
	  case 8:
		  len += sprintf(&buffer[len], "%08X%08X", Data[0], Data[1]);
		  break;
	  }
	  /* Fine messaggio */
	  len += sprintf(&buffer[len], "\r\n");
	  sd_lld_write(&SD1, buffer, len);
}

void Serial_RX_msg(void){
	Serial_Sendmsg("RX", CAN_Msg.ID, CAN_Msg.DLC, CAN_Msg.Data);
}

void Serial_TX_msg(uint32_t ID, uint8_t DLC, uint32_t *Data){
	Serial_Sendmsg("TX", ID, DLC, Data);
//	  memset(buffer, 0, sizeof(buffer));	// Cancelliamo il buffer
//	  len = 0;								// Cancelliamo il contatore
//
//	  /* ID */
//	  len += sprintf(&buffer[len], "ID=%08lX D=%d TX=", CAN_id, DLC);
//
//	  /* Payload */
//	  len += sprintf(&buffer[len], "%08lX%08lX", CAN_data[0], CAN_data[1]);
//
//	  /* Fine messaggio */
//	  len += sprintf(&buffer[len], "\r\n");
//
//	  sd_lld_write(&SD2, buffer, len);
}
