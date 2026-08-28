/*
 * LightControl_cfg.h
 *
 *  Created on: 28 ago 2025
 *      Author: Casa
 */

#ifndef CFG_LIGHTCONTROL_CFG_H_
#define CFG_LIGHTCONTROL_CFG_H_

#include "components.h"

#define CAN_ID_LIGHTCONTROL 0x400
#define CAN_DLC_LIGHTCONTROL 2

//uint8_t anabbagliante;
//uint8_t fendinebbia;
//uint8_t posizione;
//uint8_t clacson;
//uint8_t frecciaSX;
//uint8_t abbaglianteF;
//uint8_t frecciaDX;
//uint8_t abbagliante;
//uint8_t stop;

uint8_t GPIORXBuffer[2];

#define posizione     0
#define anabbagliante 1
#define retronebbia   2
#define abbagliante   3
#define stop          4
#define frecciaDX     5
#define frecciaSX     6
#define fendinebbia   7
#define retro         0

#endif /* CFG_LIGHTCONTROL_CFG_H_ */
