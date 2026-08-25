/*
 * canopen.c
 *
 *  Created on: 18 gen 2026
 *      Author: Casa
 */
#include "components.h"

//#include "timer.h"
#include "canopen.h"

#include <string.h>
#include "canopen_cfg.h"
#include "pit_lld_cfg.h"
#include "can_lld_cfg.h"
#include "solo_drive_cfg.h"

#define SDO_TIMEOUT_MS 200
#define SDO_RETRIES    1

//extern volatile bool Sync_Request_canopen;

SDO_Req_t SDO_Req_Sts;		// Flag per gestire i messaggi che arrivano
SOLOMotor_Status_TPDO_t TPDO_Sts_Motor[SOLOMOTOR_N_ECU];
/*
 * Interrupt Function
 */
void mcanconf_CAN_SoloMotor_Callback(uint32_t msgbuf, CANRxFrame crfp){
	(void) msgbuf;

	/* Gestione ricezione risposta SDO da configurazione */
	if(crfp.ID == SOLOCONTROLLER_ID1 || crfp.ID == SOLOCONTROLLER_ID2){
		if(SDO_Req_Sts.SDOFlag == SDO_WRITE_CHECK)
		{
			if((SDO_Req_Sts.index[0] == crfp.data8[1]) && (SDO_Req_Sts.index[1] == crfp.data8[2]))
			{
				(crfp.data8[0] == SDO_WRITE_POS_RESP) ? (SDO_Req_Sts.SDOFlag = SDO_Rep_Positive) : (SDO_Req_Sts.SDOFlag = SDO_Rep_Negative);  // Risposta del SDO
			}
		}
	}
	/* Stato SOLO MOTOR */
	switch(crfp.ID){
	case TPDO1_CAN_ID_BASE_1:
		break;
	case TPDO2_CAN_ID_BASE_1:
		TPDO_Sts_Motor[0].TPDO2_RPM_Fbk = crfp.data32[0];
		break;
	case TPDO3_CAN_ID_BASE_1:
		TPDO_Sts_Motor[0].TPDO3_Iq_Fbk = crfp.data32[0];
		break;
	case TPDO4_CAN_ID_BASE_1:
		TPDO_Sts_Motor[0].TPDO4_Id_Fbk = crfp.data32[0];
		break;
	case TPDO5_CAN_ID_BASE_1:
		TPDO_Sts_Motor[0].TPDO5_ErrorRegister = crfp.data8[0];
		break;
	case TPDO6_CAN_ID_BASE_1:
		TPDO_Sts_Motor[0].TPDO6_TempBoard = crfp.data32[0] / 131072;
		break;
	}
}

/* Init CAN module */
void CANopen_Init(void){
	can_lld_init();
	can_lld_start(&CANMODULE, &can_config_mcanconf);
}

uint32_t CAN_GetMillis(void){
	return osalThreadGetMilliseconds();
}

bool CAN_Send(const CAN_Frame *frame){

	static CANTxFrame CAN_Tx_Frame;
	// Default configuration CAN Tx Frame
	CAN_Tx_Frame.OPERATION 	= CAN_OP_NORMAL;
	CAN_Tx_Frame.TYPE 		= CAN_ID_STD;

	// confgiuration msg
	CAN_Tx_Frame.ID 	= frame->id;
	CAN_Tx_Frame.DLC 	= frame->dlc;
	if(frame->dlc != 0) memcpy(CAN_Tx_Frame.data8, frame->data, SPC5_CAN_MAX_DATA_LENGHT); // Copia i dati da un parte all'altra

	// Send data
	if(can_lld_transmit(&CANMODULE, CAN_ANY_TXBUFFER, &CAN_Tx_Frame) != CAN_MSG_OK) return false;

	return TRUE;
}

bool CANopen_SDO_Write(uint8_t node, uint16_t index, uint8_t sub, uint32_t value)
{
    CAN_Frame tx;
    tx.id  = CANOPEN_SDO_TX(node);
    tx.dlc = 8;

    tx.data[0] = SDO_WRITE_REQUEST;
    tx.data[1] = index & 0xFF;
    tx.data[2] = index >> 8;
    tx.data[3] = sub;
    tx.data[4] = value & 0xFF;
    tx.data[5] = value >> 8;
    tx.data[6] = value >> 16;
    tx.data[7] = value >> 24;

    CAN_Send(&tx);
    uint32_t t0 = CAN_GetMillis();

    SDO_Req_Sts.SDOFlag = SDO_WRITE_CHECK;
    SDO_Req_Sts.index[0] =  index & 0xFF;
    SDO_Req_Sts.index[1] =  index >> 8;

    while(CAN_GetMillis() - t0 < SDO_TIMEOUT_MS)
    {
    	if(SDO_Req_Sts.SDOFlag == SDO_Rep_Positive) return TRUE;
    }
    return FALSE;
}

uint8_t CANopen_SDO_Read(uint8_t node, uint16_t index, uint8_t sub)
{
    CAN_Frame tx;
    tx.id = CANOPEN_SDO_TX(node);
    tx.dlc = 8;

    tx.data[0] = 0x40;
    tx.data[1] = index & 0xFF;
    tx.data[2] = index >> 8;
    tx.data[3] = sub;
    tx.data[4] = 0x00;
    tx.data[5] = 0x00;
    tx.data[6] = 0x00;
    tx.data[7] = 0x00;

    if(CAN_Send(&tx) != true) return CAN_SDO_FAIL_TX_MSG;

    uint32_t t0 = CAN_GetMillis();

    while((CAN_GetMillis() - t0 < SDO_TIMEOUT_MS))
    {
    	if(SDO_Req_Sts.SDOFlag == SDO_Rep_Positive) return CAN_SDO_OK;
    	if(SDO_Req_Sts.SDOFlag == SDO_Rep_Negative) return CAN_SDO_TIMEOUT_MSG;
    }

    return CAN_SDO_TIMEOUT_MSG;
}

void CANopen_SYNC_NMT(void)
{
    CAN_Frame f;

    f.dlc = 1;
    f.id = CAN_NMT_ID;
    CAN_Send(&f);
}

void CANopen_SendSYNC(void)
{
//    CAN_Frame f = { CANOPEN_SYNC_ID, 0, {0} };
//    if(CAN_Send(&f) != true) printf("Error SendSYNC\r\n");
}


