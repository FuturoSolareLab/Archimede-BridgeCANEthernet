/*
 * solo_driver.h
 *
 *  Created on: 18 gen 2026
 *      Author: Casa
 */

#ifndef INC_SOLO_DRIVE_H_
#define INC_SOLO_DRIVE_H_

#include <stdint.h>
#include <stdbool.h>
#include "can_hal.h"
#include "components.h"

/* TPDO ID */
#define TPDO2_ID	 	0x1815 // Feedback Velocity
#define TPDO3_ID	 	0x1816 // Feedback Iq
#define TPDO4_ID	 	0x1817 // Feedback Id
#define TPDO5_ID	 	0x1818 // Error Register
#define TPDO6_ID	 	0x1819 // Board Temperature

#define TPDO_DISABLE_MASK 			0xC0000000
#define SDO_POSITIVE_RESPONSE 		0x60

typedef struct {
    float Iq;
    float Id;
    int32_t speed;
    float bus_voltage;
    float temperature;
    uint32_t last_heartbeat;
    bool fault;
} SOLO_State;

extern SOLO_State solo[3];

bool SOLO_Init(uint8_t node);
bool SOLO_Enable(uint8_t node);
void SOLO_NMT_Status(uint8_t NMT_Status);
void SOLO_SetTorque(uint8_t node, int32_t torque);

void SOLO_HandleTPDO(const CAN_Frame *f);
void SOLO_ReadBusVoltage(uint8_t node);

#endif /* INC_SOLO_DRIVE_H_ */
