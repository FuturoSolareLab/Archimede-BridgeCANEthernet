/*
 * can_hal.c
 *
 *  Created on: 18 gen 2026
 *      Author: Andrea
 *
 *      Usato per communicare con i motori.
 *      Questo modulo serve a inviare i msg CAN solo ai motori
 */

#include "can_hal.h"
#include <string.h>
#include "components.h"



CANTxFrame CAN_Tx_Frame;
CANRxFrame CAN_Rx_Frame;

Handle_CANFramemsg_t CAN_Msg;
uint8_t Handle_Req_newmsg = FALSE;



void mcanconf_CAN_Vehicle_Rx_Callback(uint32_t msgbuf, CANRxFrame crfp) {
	(void) msgbuf;  // Default
	(void) crfp;

	/* Salviamo i dati */
	CAN_Msg.ID = crfp.ID;
	CAN_Msg.DLC = crfp.DLC;
	CAN_Msg.Data[0] = crfp.data32[0];
	CAN_Msg.Data[1] = crfp.data32[1];

	Handle_Req_newmsg = TRUE;		// Abbilitiamo il flag
}

/*
 * Interrupt Function
 */
//void mcanconf_CANrxreceive(uint32_t msgbuf, CANRxFrame crfp){
//	(void) msgbuf;
//	(void) crfp;
//}
//void mcanconf_CAN_Vehicle_Rx_Callback(uint32_t msgbuf, CANRxFrame crfp){
//	(void) msgbuf;
//	(void) crfp;
//}



//bool CAN_Send(const CAN_Frame *frame){
//
//	// Default configuration CAN Tx Frame
//	CAN_Tx_Frame.OPERATION 	= CAN_OP_NORMAL;
//	CAN_Tx_Frame.TYPE 		= CAN_ID_STD;
//
//	// confgiuration msg
//	CAN_Tx_Frame.ID 	= frame->id;
//	CAN_Tx_Frame.DLC 	= frame->dlc;
//	if(frame->dlc != 0) memcpy(CAN_Tx_Frame.data8, frame->data, SPC5_CAN_MAX_DATA_LENGHT); // Copia i dati da un parte all'altra
//
//	// Send data
//	if(can_lld_transmit(&CANMODULE, CAN_ANY_TXBUFFER, &CAN_Tx_Frame) != CAN_MSG_OK) return false;
//
//	return TRUE;
//}

bool CAN_Receive(CAN_Frame *frame){
	return TRUE;
}



void CAN_DelayMs(uint32_t ms){
	osalThreadDelayMilliseconds(ms);
}
