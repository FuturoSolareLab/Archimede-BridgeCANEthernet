/*
 * solo_driver.c
 *
 *  Created on: 18 gen 2026
 *      Author: Casa
 */


#include "solo_drive.h"
#include "solo_drive_cfg.h"
#include "canopen.h"
#include "components.h"

SOLO_State solo[3];

bool SOLO_Init(uint8_t node)
{

    CAN_DelayMs(500);

    CANopen_SDO_Write(node, IDX_HEARTBEAT, 0x00, 5000);
    CANopen_SDO_Write(node, IDX_MODE, 0x00, 4);


    return true;
}

bool SOLO_Enable(uint8_t node)
{
    CANopen_SDO_Write(node, IDX_CONTROLWORD, 0x00, 0x0006);
    CAN_DelayMs(10);
    CANopen_SDO_Write(node, IDX_CONTROLWORD, 0x00, 0x0007);
    CAN_DelayMs(10);
    CANopen_SDO_Write(node, IDX_CONTROLWORD, 0x00, 0x000F);
    return true;
}

void SOLO_NMT_Status(uint8_t NMT_Status){
    CANopen_SendNMT(NMT_Status, 0);
}

void SOLO_TPDO_Setting(uint8_t node){

	if(node == NODE_1_ID) {
		/* Configure/Init TPDO2_ID Feedback Velocity */
		CANopen_SDO_Write(node, TPDO2_ID, TPDO_DISABLE, TPDO_DISABLE_MASK + TPDO2_CAN_ID_BASE_1);
		CANopen_SDO_Write(node, TPDO2_ID, TPDO_ACTIVE, TPDO_DELAY_SYNC);

		/* Configure/Init TPDO3_ID Feedback Iq */
		CANopen_SDO_Write(node, TPDO3_ID, TPDO_DISABLE, TPDO_DISABLE_MASK + TPDO3_CAN_ID_BASE_1);
		CANopen_SDO_Write(node, TPDO3_ID, TPDO_ACTIVE, TPDO_DELAY_SYNC);

		/* Configure/Init TPDO4_ID Feedback Id */
		CANopen_SDO_Write(node, TPDO4_ID, TPDO_DISABLE, TPDO_DISABLE_MASK + TPDO4_CAN_ID_BASE_1);
		CANopen_SDO_Write(node, TPDO4_ID, TPDO_ACTIVE, TPDO_DELAY_SYNC);

		/* Configure/Init TPDO5_ID Error Register */
		CANopen_SDO_Write(node, TPDO5_ID, TPDO_DISABLE, TPDO_DISABLE_MASK + TPDO5_CAN_ID_BASE_1);
		CANopen_SDO_Write(node, TPDO5_ID, TPDO_ACTIVE, TPDO_DELAY_SYNC);

		/* Configure/Init TPDO6_ID Error Register */
		CANopen_SDO_Write(node, TPDO6_ID, TPDO_DISABLE, TPDO_DISABLE_MASK + TPDO6_CAN_ID_BASE_1);
		CANopen_SDO_Write(node, TPDO6_ID, TPDO_ACTIVE, TPDO_DELAY_SYNC);
	}

	if(node == NODE_2_ID) {
		/* Configure/Init TPDO2_ID Feedback Velocity */
		CANopen_SDO_Write(node, TPDO2_ID, TPDO_DISABLE, TPDO_DISABLE_MASK + TPDO2_CAN_ID_BASE_2);
		CANopen_SDO_Write(node, TPDO2_ID, TPDO_ACTIVE, TPDO_DELAY_SYNC);

		/* Configure/Init TPDO3_ID Feedback Iq */
		CANopen_SDO_Write(node, TPDO3_ID, TPDO_DISABLE, TPDO_DISABLE_MASK + TPDO3_CAN_ID_BASE_2);
		CANopen_SDO_Write(node, TPDO3_ID, TPDO_ACTIVE, TPDO_DELAY_SYNC);

		/* Configure/Init TPDO4_ID Feedback Id */
		CANopen_SDO_Write(node, TPDO4_ID, TPDO_DISABLE, TPDO_DISABLE_MASK + TPDO4_CAN_ID_BASE_2);
		CANopen_SDO_Write(node, TPDO4_ID, TPDO_ACTIVE, TPDO_DELAY_SYNC);

		/* Configure/Init TPDO5_ID Error Register */
		CANopen_SDO_Write(node, TPDO5_ID, TPDO_DISABLE, TPDO_DISABLE_MASK + TPDO5_CAN_ID_BASE_2);
		CANopen_SDO_Write(node, TPDO5_ID, TPDO_ACTIVE, TPDO_DELAY_SYNC);

		/* Configure/Init TPDO6_ID Error Register */
		CANopen_SDO_Write(node, TPDO6_ID, TPDO_DISABLE, TPDO_DISABLE_MASK + TPDO6_CAN_ID_BASE_2);
		CANopen_SDO_Write(node, TPDO6_ID, TPDO_ACTIVE, TPDO_DELAY_SYNC);
	}


}
