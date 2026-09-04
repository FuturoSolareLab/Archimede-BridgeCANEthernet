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
#include "pit_lld_cfg.h"
#include "LightControl.h"
#include "PowerMng.h"

#include "can_hal.h"

#define ID_CAN_BMS 0x0400FF80
#define ID_CAN_SOLOMOTOR 0x80


/* TIMER NMT
 * Define timer for Network manager, base timer 100ms */
#define TIMER_NMT_SOLOMOTOR		5 // Time 500ms
#define TIMER_NMT_BMS			20 // Timer 2000 ms
#define TIMER_LIGHT			5 // Time 500ms (nel progetto CentralUnit è 100ms)

uint8_t TIMER_cnt = 0;			// Counter tick
uint8_t TIMER_Flag = FALSE;

/* CAN msg */
extern uint8_t Handle_Req_newmsg;	// Flag per inviare il msg

CANTxFrame BMS_msg;
CANTxFrame SOLOMotor_msg;
CANTxFrame* LIGHT_msg;


/* Incaso di errore di inviao sulla seriale */
void Serial_DMA_ErrorCbck(SerialDriver *sdp){
	 (void) sdp;
}

/* TIMER CALLBCK */
void Timer_tick_CallBck(void){
	TIMER_cnt++;
	TIMER_Flag = TRUE;
}

/* CAN interrupt */
void mcanconf_CANrxreceive(uint32_t msgbuf, CANRxFrame crfp) {
	(void) msgbuf;  // Default
	(void) crfp;

//	/* Salviamo i dati */
//	CAN_id = crfp.ID;
//	CAN_DLC = crfp.DLC;
//	CAN_data[0] = crfp.data32[0];
//	CAN_data[1] = crfp.data32[1];
//
//	Handle_Req_newmsg = TRUE;		// Abbilitiamo il flag
}

/* Inizializzazione periferiche */
void Init_Periferiche(void){
	can_lld_init();								   	  // CAN peripherals Init
	can_lld_start(&CAND1, &can_config_mcanconf);      // Configuration Driver communication

	sd_lld_init();
	sd_lld_start(&SD1, &serial_config_configuration_name);

	pit_lld_init();
	pit_lld_start(&PITD1, pit0_config);
	pit_lld_channel_start(&PITD1, PIT0_CHANNEL_CH1);
}

void Init_CAN_msg(void){
	BMS_msg.OPERATION = CAN_OP_NORMAL;
	BMS_msg.TYPE = CAN_ID_XTD;
	BMS_msg.ID	= ID_CAN_BMS;
	BMS_msg.DLC = 8;
	BMS_msg.data32[0] = 0x00;
	BMS_msg.data32[1] = 0x00;


	SOLOMotor_msg.OPERATION = CAN_OP_NORMAL;
	SOLOMotor_msg.TYPE = CAN_ID_STD;
	SOLOMotor_msg.ID	= ID_CAN_SOLOMOTOR;
	SOLOMotor_msg.DLC = 1;
	SOLOMotor_msg.data32[0] = 0x00;
	SOLOMotor_msg.data32[1] = 0x00;
}

/*
 * Application entry point.
 */
int main(void) {

  /* Initialization of all the imported components in the order specified in
     the application wizard. The function is generated automatically.*/
  componentsInit();

  Init_Periferiche();

  Init_CAN_msg();

  /* Uncomment the below routine to Enable Interrupts. */
   irqIsrEnable();
   SOLO_TPDO_Setting(1);
  /* Application main loop.*/
  for ( ; ; ) {
	  if(Handle_Req_newmsg == TRUE){
		  Handle_Req_newmsg = FALSE;
		  Serial_RX_msg();

	  }
	  if(TIMER_Flag){
		  TIMER_Flag = FALSE;
		  if(TIMER_cnt % TIMER_NMT_BMS == 0){
			  /* Invio messaggio per i BMS */
			  can_lld_transmit(&CAND1, CAN_ANY_TXBUFFER, &BMS_msg);
			  Serial_TX_msg(BMS_msg.ID, BMS_msg.DLC, BMS_msg.data32);
		  }
		  if(TIMER_cnt % TIMER_NMT_SOLOMOTOR == 0){
			  /* Invio NMT per i driver SOLO */
			  can_lld_transmit(&CAND1, CAN_ANY_TXBUFFER, &SOLOMotor_msg);
			  Serial_TX_msg(SOLOMotor_msg.ID, SOLOMotor_msg.DLC, SOLOMotor_msg.data32);
		  }
		  if(TIMER_cnt % TIMER_LIGHT == 0){
			  /*invio stato luci*/
			  LIGHT_msg = LightControl_GetStatus();
			  can_lld_transmit(&CAND1, CAN_ANY_TXBUFFER, &LIGHT_msg);
			  Serial_TX_msg(LIGHT_msg->ID, LIGHT_msg->DLC, LIGHT_msg->data32);
		  }
		  if(TIMER_cnt == 100) TIMER_cnt = 0;
	  }
  }
}
