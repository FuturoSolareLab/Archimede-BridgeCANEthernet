/*
 * PowerMng_cfg.h
 *
 *  Created on: 4 set 2026
 *      Author: Casa
 */

#ifndef CFG_POWERMNG_CFG_H_
#define CFG_POWERMNG_CFG_H_

#define MIN_BATTERY_VALUE 			280U	// 28V
#define MAX_BATTERY_VALUE			553U	// 55.3V --> 0.1V/bit

#define VBUS_LOW_VALUE				150U	// 15V

#define MAX_DELTA_V_BATTERY_PRESTS        	40U   	// 4V --> 0.1V/bit differenza massima tra Batt1 e Batt2
#define MAX_DELTA_V_VBUS_BATTERY_PRESTS   	10U  	// 1V --> 0.1V/bit differenza massima tra Vbus e batteria

#define MAX_DELTA_V_BATTERY_OPSTS        	20U   	// 2V --> 0.1V/bit differenza massima tra Batt1 e Batt2


// messaggio CAN
#define CAN_ID_RELSTS			0x236
#define CAN_DLC_RELST			1U

#define CAN_POS_RELPRECHARGE1	0U	// Posizione del bit sul byte
#define CAN_POS_RELPRECHARGE2	1U	// Posizione del bit sul byte
#define CAN_POS_RELPOWER1		2U	// Posizione del bit sul byte
#define CAN_POS_RELPOWER2		3U	// Posizione del bit sul byte

#endif /* CFG_POWERMNG_CFG_H_ */
