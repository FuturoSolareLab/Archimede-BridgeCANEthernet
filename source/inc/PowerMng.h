/*
 * PowerMng.h
 *
 *  Created on: 4 set 2026
 *      Author: Casa
 */

#ifndef INC_POWERMNG_H_
#define INC_POWERMNG_H_

#include "components.h"


/* MPPT	*/
#define ID_MPPT_INA_PV1			0x701
#define ID_MPPT_INA_PV2			0x702
#define ID_MPPT_INA_PV3			0x703
#define ID_MPPT_Status			0x704
#define ID_MPPT_Temp			0x705
/* BMS 1 */
#define ID_BMS1_TotInfor1		0x04028001
#define ID_BMS1_TotInfor2		0x04038001
/* BMS 2 */
#define ID_BMS2_TotInfor1		0x04028002
#define ID_BMS2_TotInfor2		0x04038002

void SendCAN_CommandRele(void);
uint8_t PowerMng(void);


typedef enum{
	Mng_Init = 0,
	Mng_PreOperation,
	Mng_Operation,
	Mng_PreOFF,
	Mng_OFF
}Macchine_Sts_e;

#endif /* INC_POWERMNG_H_ */
