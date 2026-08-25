/*
 * can_hal.h
 *
 *  Created on: 18 gen 2026
 *      Author: Casa
 */

#ifndef INC_CAN_HAL_H_
#define INC_CAN_HAL_H_

#include <stdint.h>
#include <stdbool.h>
#include "components.h"
#include "can_lld_cfg.h"

typedef struct {
    uint32_t id;
    uint8_t  dlc;
    uint8_t  data[8];
} CAN_Frame;

typedef struct {
    uint32_t ID; 		// Variabile tmp per salvare il CAN ID
    uint8_t  DLC;		// Variabile tmp per salvare il CAN DLC
    uint32_t Data[2];	// Variabile tmp per salvare il CAN payload
} Handle_CANFramemsg_t;


bool CAN_Send(const CAN_Frame *frame);
bool CAN_Receive(CAN_Frame *frame);

uint32_t CAN_GetMillis(void);
void CAN_DelayMs(uint32_t ms);

#endif /* INC_CAN_HAL_H_ */
