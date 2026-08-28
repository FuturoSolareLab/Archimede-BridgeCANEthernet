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

uint8_t GPIORXBuffer;

#define posizione     0
#define anabbagliante 1
#define abbagliante   2
#define stop          3
#define frecciaDX     4
#define frecciaSX     5
#define retro         6

#endif /* CFG_LIGHTCONTROL_CFG_H_ */
