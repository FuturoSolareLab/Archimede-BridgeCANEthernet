/*
 * canopen.h
 *
 *  Created on: 18 gen 2026
 *      Author: Casa
 */

#ifndef INC_CANOPEN_H_
#define INC_CANOPEN_H_


#include <stdint.h>
#include <stdbool.h>
#include "can_hal.h"

/* CANopen base IDs */
#define CAN_NMT_ID        		0x80

#define CANOPEN_SDO_TX(n)     (0x600 + (n))
#define CANOPEN_SDO_RX(n)     (0x580 + (n))
#define CANOPEN_HEARTBEAT(n)  (0x700 + (n))
#define CANOPEN_EMCY(n)       (0x080 + (n))

/* SDO Response */
#define SDO_WRITE_REQUEST		0x22
#define SDO_READ_REQUEST		0x40
#define SDO_WRITE_POS_RESP		0x60
#define SDO_READ_POS_RESP		0x42



/* NMT commands */
#define NMT_START             0x01
#define NMT_RESET_NODE        0x81

/* Status SDO msg */
#define CAN_SDO_OK 				0x0
#define CAN_SDO_TIMEOUT_MSG		0x1
#define CAN_SDO_FAIL_TX_MSG		0x2

#define SOLOCONTROLLER_ID1		0x581
#define SOLOCONTROLLER_ID2		0x582

typedef enum{
	SDO_WRITE_CHECK,
	SDO_READ_CHECK,
	SDO_Rep_Positive,
	SDO_Rep_Negative,
	SDO_WAIT
}SDO_Req_enum;

typedef struct{
	uint8_t 	ID_Driver;
	uint16_t 	TPDO1_TempMotor; 		// Position Feedback
	uint32_t 	TPDO2_RPM_Fbk; 			// Speed feedback
	uint16_t 	TPDO3_Iq_Fbk; 			// Torque Feedback
	uint16_t 	TPDO4_Id_Fbk;			// Direct Current Feedback
	uint8_t 	TPDO5_ErrorRegister; 	// Error Register
	uint16_t 	TPDO6_TempBoard;		// Board Temperature
} SOLOMotor_Status_TPDO_t;

typedef struct{
	int8_t index[2];
	SDO_Req_enum SDOFlag;
}SDO_Req_t;

void CANopen_Init(void);
bool CANopen_SDO_Write(uint8_t node, uint16_t index, uint8_t sub, uint32_t value);
uint8_t CANopen_SDO_Read (uint8_t node, uint16_t index, uint8_t sub);

void CANopen_SYNC_NMT(void);
void CANopen_SendSYNC(void);

void CanOpen_Monitor_Task(void);

#endif /* INC_CANOPEN_H_ */
