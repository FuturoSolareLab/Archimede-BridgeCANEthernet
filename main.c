/****************************************************************************
*
* Copyright © 2015-2021 STMicroelectronics - All Rights Reserved
*
* This software is licensed under SLA0098 terms that can be found in the
* DM00779817_1_0.pdf file in the licenses directory of this software product.
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
*****************************************************************************/

/* Inclusion of the main header files of all the imported components in the
   order specified in the application wizard. The file is generated
   automatically.*/
#include "components.h"

#include "can_lld_cfg.h"
#include "serial_lld_cfg.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t buffer[64];		// Buffer per invio messaggio su seriale		--> char e uint8_t sono uguali

uint8_t CAN_id = 0;		// Variabile tmp per salvare il CAN ID
uint8_t CAN_DLC = 0;	// Variabile tmp per salvare il CAN DLC
uint32_t	CAN_data[2];	// Variabile tmp per salvare il CAN payload

uint8_t New_msg = FALSE;	// Flag per inviare il msg
uint16_t len = 0;			// Variabile per salvare la sungezza msg

/* Incaso di errore di inviao sulla seriale */
void Serial_DMA_ErrorCbck(SerialDriver *sdp){
	 (void) sdp;
}

/* CAN interrupt */
void mcanconf_CANrxreceive(uint32_t msgbuf, CANRxFrame crfp) {
	(void) msgbuf;  // Default
	(void) crfp;

	/* Salviamo i dati */
	CAN_id = crfp.ID;
	CAN_DLC = crfp.DLC;
	CAN_data[0] = crfp.data32[0];
	CAN_data[1] = crfp.data32[1];

	New_msg = TRUE;		// Abbilitiamo il flag
}


/* Inizializzazione periferiche */
void Init_Periferiche(void){
	can_lld_init();								   	  // CAN peripherals Init
	can_lld_start(&CAND1, &can_config_mcanconf);      // Configuration Driver communication

	sd_lld_init();
	sd_lld_start(&SD1, &serial_config_configuration_name);
}

/*
 * Application entry point.
 */
int main(void) {

  /* Initialization of all the imported components in the order specified in
     the application wizard. The function is generated automatically.*/
  componentsInit();

  Init_Periferiche();

  /* Uncomment the below routine to Enable Interrupts. */
   irqIsrEnable();
  
  /* Application main loop.*/
  for ( ; ; ) {
	  if(New_msg == TRUE){
		  New_msg = FALSE;

		  memset(buffer, 0, sizeof(buffer));	// Cancelliamo il buffer
		  len = 0;								// Cancelliamo il contatore

		  /* ID */
		  len += sprintf(&buffer[len], "ID=%02X P=", CAN_id);

		  /* Payload */
		  len += sprintf(&buffer[len], "%08lX%08lX", CAN_data[0], CAN_data[1]);

		  /* Fine messaggio */
		  len += sprintf(&buffer[len], "\r\n");

		  sd_lld_write(&SD1, buffer, len);
	  }
  }
}
