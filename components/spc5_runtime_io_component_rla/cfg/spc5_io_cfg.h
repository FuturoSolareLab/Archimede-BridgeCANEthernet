/***********************************************************************************
*
* Copyright © 2017-2019 STMicroelectronics - All Rights Reserved
*
* This software is licensed under SLA0098 terms that can be found in the
* DM00779817_1_0.pdf file in the licenses directory of this software product.
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
************************************************************************************/
/**
 * @file    spc5_io_cfg.h
 * @brief   SPC5 Runtime I/O configuration file.
 *
 * @addtogroup SPC5_RUNTIME_IO
 * @{
 */

#ifndef _SPC5_IO_CFG_H_
#define _SPC5_IO_CFG_H_

#include "spc5_lld.h"
#include "lldconf.h"

#define LINFlex0					1U
#define LINFlex1					2U
#define LINFlex2					3U
#define LINFlex3					4U
#define LINFlex4					5U
#define LINFlex5					6U
#define LINFlex6					7U
#define LINFlex7					8U
#define LINFlex8					9U
#define LINFlex9					10U
#define LINFlex10					11U
#define LINFlex11					12U
#define LINFlex12					13U
#define LINFlex13					14U
#define LINFlex14					15U
#define LINFlex15					16U
#define LINFlex16					17U
#define LINFlex17					18U
#define LINFlex18					19U
#define LINFlex19					20U
#define LINFlex20					21U
#define LINFlex21					22U
#define LINFlex22					23U
#define LINFlex23					24U

#define ESCI0						100U
#define ESCI1						101U
#define ESCI2						102U

#define Sub0Can0					200U
#define Sub0Can1					201U
#define Sub0Can2					202U
#define Sub0Can3					203U
#define Sub0Can4					204U
#define Sub1Can0					205U
#define Sub1Can1					206U
#define Sub1Can2					207U
#define Sub1Can3					208U
#define Sub1Can4					209U

#define FlexCan0					300U
#define FlexCan1					301U
#define FlexCan2					302U
#define FlexCan3					303U
#define FlexCan4					304U
#define FlexCan5					305U

#define NONE						255U

#define PRINTF_USE_NONE				TRUE
#define PRINTF_USE_SERIAL			FALSE
#define PRINTF_USE_CAN				FALSE
#define PRINTF_USE_ETH				FALSE

#if PRINTF_USE_SERIAL

#define SERIAL_TO_USE              NONE

#if (SERIAL_TO_USE == NONE)
#error "Please select the Serial device to use in IO Runtime Settings!"
#endif

#define SPC5_IO_DEVICE_TYPE			SPC5_IO_DEVICE_SERIAL

/* Serial port configuration */
#define RUNTIME_IO_SERIAL_CONF_BAUDRATE     38400U
#define RUNTIME_IO_SERIAL_CONF_DATA_LENGTH  8U
#define RUNTIME_IO_SERIAL_CONF_PARITY       NONE
#define RUNTIME_IO_SERIAL_CONF_STOP_BITS    1

#define RUNTIME_IO_SERIAL_MODE              SD_MODE_8BITS_PARITY_NONE


#if (SERIAL_TO_USE == LINFlex0) && (SPC5_LINFLEX0_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-0 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex1) && (SPC5_LINFLEX1_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-1 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex2) && (SPC5_LINFLEX2_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-2 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex3) && (SPC5_LINFLEX3_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-3 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex4) && (SPC5_LINFLEX4_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-4 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex5) && (SPC5_LINFLEX5_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-5 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex6) && (SPC5_LINFLEX6_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-6 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex7) && (SPC5_LINFLEX7_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-7 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex8) && (SPC5_LINFLEX8_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-8 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex9) && (SPC5_LINFLEX9_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-9 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex10) && (SPC5_LINFLEX10_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-10 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex11) && (SPC5_LINFLEX11_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-11 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex12) && (SPC5_LINFLEX12_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-12 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex13) && (SPC5_LINFLEX13_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-13 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex14) && (SPC5_LINFLEX14_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-14 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex15) && (SPC5_LINFLEX15_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-15 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex16) && (SPC5_LINFLEX16_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-16 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex17) && (SPC5_LINFLEX17_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-17 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex18) && (SPC5_LINFLEX18_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-18 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex19) && (SPC5_LINFLEX19_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-19 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex20) && (SPC5_LINFLEX20_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-20 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex21) && (SPC5_LINFLEX21_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-21 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex22) && (SPC5_LINFLEX22_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-22 as serial printf device but not enabled in LINFLEX settings!"
#endif
#if (SERIAL_TO_USE == LINFlex23) && (SPC5_LINFLEX23_SETTING != SPC5_LINFLEX_MODE_SERIAL)
#error "Selected LINFlex-23 as serial printf device but not enabled in LINFLEX settings!"
#endif

#if (SERIAL_TO_USE == ESCI0) && (SPC5_USE_ESCIA == FALSE)
#error "Selected ESCI0 as serial printf device but not enabled in eSCI settings!"
#endif
#if (SERIAL_TO_USE == ESCI1) && (SPC5_USE_ESCIB == FALSE)
#error "Selected ESCI1 as serial printf device but not enabled in eSCI settings!"
#endif
#if (SERIAL_TO_USE == ESCI2) && (SPC5_USE_ESCIC == FALSE)
#error "Selected ESCI2 as serial printf device but not enabled in eSCI settings!"
#endif

#if (SERIAL_TO_USE == LINFlex0)
#define SPC5_IO_DEVICE_NAME		"serial1"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD1
#endif
#if (SERIAL_TO_USE == LINFlex1)
#define SPC5_IO_DEVICE_NAME		"serial2"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD2
#endif
#if (SERIAL_TO_USE == LINFlex2)
#define SPC5_IO_DEVICE_NAME		"serial3"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD3
#endif
#if (SERIAL_TO_USE == LINFlex3)
#define SPC5_IO_DEVICE_NAME		"serial4"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD4
#endif
#if (SERIAL_TO_USE == LINFlex4)
#define SPC5_IO_DEVICE_NAME		"serial5"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD5
#endif
#if (SERIAL_TO_USE == LINFlex5)
#define SPC5_IO_DEVICE_NAME		"serial6"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD6
#endif
#if (SERIAL_TO_USE == LINFlex6)
#define SPC5_IO_DEVICE_NAME		"serial7"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD7
#endif
#if (SERIAL_TO_USE == LINFlex7)
#define SPC5_IO_DEVICE_NAME		"serial8"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD8
#endif
#if (SERIAL_TO_USE == LINFlex8)
#define SPC5_IO_DEVICE_NAME		"serial9"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD9
#endif
#if (SERIAL_TO_USE == LINFlex9)
#define SPC5_IO_DEVICE_NAME		"serial10"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD10
#endif
#if (SERIAL_TO_USE == LINFlex10)
#define SPC5_IO_DEVICE_NAME		"serial11"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD11
#endif
#if (SERIAL_TO_USE == LINFlex11)
#define SPC5_IO_DEVICE_NAME		"serial12"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD12
#endif
#if (SERIAL_TO_USE == LINFlex12)
#define SPC5_IO_DEVICE_NAME		"serial13"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD13
#endif
#if (SERIAL_TO_USE == LINFlex13)
#define SPC5_IO_DEVICE_NAME		"serial14"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD14
#endif
#if (SERIAL_TO_USE == LINFlex14)
#define SPC5_IO_DEVICE_NAME		"serial15"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD15
#endif
#if (SERIAL_TO_USE == LINFlex15)
#define SPC5_IO_DEVICE_NAME		"serial16"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD16
#endif
#if (SERIAL_TO_USE == LINFlex16)
#define SPC5_IO_DEVICE_NAME		"serial17"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD17
#endif
#if (SERIAL_TO_USE == LINFlex17)
#define SPC5_IO_DEVICE_NAME		"serial18"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD18
#endif
#if (SERIAL_TO_USE == LINFlex18)
#define SPC5_IO_DEVICE_NAME		"serial19"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD19
#endif
#if (SERIAL_TO_USE == LINFlex19)
#define SPC5_IO_DEVICE_NAME		"serial20"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD20
#endif
#if (SERIAL_TO_USE == LINFlex20)
#define SPC5_IO_DEVICE_NAME		"serial21"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD21
#endif
#if (SERIAL_TO_USE == LINFlex21)
#define SPC5_IO_DEVICE_NAME		"serial22"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD22
#endif
#if (SERIAL_TO_USE == LINFlex22)
#define SPC5_IO_DEVICE_NAME		"serial23"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD23
#endif
#if (SERIAL_TO_USE == LINFlex23)
#define SPC5_IO_DEVICE_NAME		"serial24"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD24
#endif

#if (SERIAL_TO_USE == ESCI0)
#define SPC5_IO_DEVICE_NAME		"serial1"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD1
#endif
#if (SERIAL_TO_USE == ESCI1)
#define SPC5_IO_DEVICE_NAME		"serial2"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD2
#endif
#if (SERIAL_TO_USE == ESCI2)
#define SPC5_IO_DEVICE_NAME		"serial3"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&SD3
#endif

#ifndef SPC5_IO_DEVICE_NAME
#error "Please fill the Device Set By User field (Serial Choice) with a correct device name to use as serial device!"
#endif

#endif /* PRINTF_USE_SERIAL */

#if PRINTF_USE_CAN

#include "can_lld_cfg.h"	/* To take the CAN configuration structure pointer. */


#define CAN_TO_USE              NONE

#if (CAN_TO_USE == NONE)
#error "Please select the CAN device to use in IO Runtime Settings!"
#endif

#if (CAN_TO_USE == Sub0Can0) && (SPC5_USE_CAN_SUB_0_M_CAN_0 == FALSE)
#error "Selected Sub0Can0 device for printf but not enabled in MCAN settings!"
#endif
#if (CAN_TO_USE == Sub0Can1) && (SPC5_USE_CAN_SUB_0_M_CAN_1 == FALSE)
#error "Selected Sub0Can1 device for printf but not enabled in MCAN settings!"
#endif
#if (CAN_TO_USE == Sub0Can2) && (SPC5_USE_CAN_SUB_0_M_CAN_2 == FALSE)
#error "Selected Sub0Can2 device for printf but not enabled in MCAN settings!"
#endif
#if (CAN_TO_USE == Sub0Can3) && (SPC5_USE_CAN_SUB_0_M_CAN_3 == FALSE)
#error "Selected Sub0Can3 device for printf but not enabled in MCAN settings!"
#endif
#if (CAN_TO_USE == Sub0Can4) && (SPC5_USE_CAN_SUB_0_M_CAN_4 == FALSE)
#error "Selected Sub0Can4 device for printf but not enabled in MCAN settings!"
#endif
#if (CAN_TO_USE == Sub1Can0) && (SPC5_USE_CAN_SUB_1_M_CAN_0 == FALSE)
#error "Selected Sub1Can0 device for printf but not enabled in MCAN settings!"
#endif
#if (CAN_TO_USE == Sub1Can1) && (SPC5_USE_CAN_SUB_1_M_CAN_1 == FALSE)
#error "Selected Sub1Can1 device for printf but not enabled in MCAN settings!"
#endif
#if (CAN_TO_USE == Sub1Can2) && (SPC5_USE_CAN_SUB_1_M_CAN_2 == FALSE)
#error "Selected Sub1Can2 device for printf but not enabled in MCAN settings!"
#endif
#if (CAN_TO_USE == Sub1Can3) && (SPC5_USE_CAN_SUB_1_M_CAN_3 == FALSE)
#error "Selected Sub1Can3 device for printf but not enabled in MCAN settings!"
#endif
#if (CAN_TO_USE == Sub1Can4) && (SPC5_USE_CAN_SUB_1_M_CAN_4 == FALSE)
#error "Selected Sub1Can4 device for printf but not enabled in MCAN settings!"
#endif

#if (CAN_TO_USE == FlexCan0) && (SPC5_CAN_USE_FLEXCAN0 == FALSE)
#error "Selected FlexCan0 device for printf but not enabled in FlexCAN settings!"
#endif
#if (CAN_TO_USE == FlexCan1) && (SPC5_CAN_USE_FLEXCAN1 == FALSE)
#error "Selected FlexCan1 device for printf but not enabled in FlexCAN settings!"
#endif
#if (CAN_TO_USE == FlexCan2) && (SPC5_CAN_USE_FLEXCAN2 == FALSE)
#error "Selected FlexCan2 device for printf but not enabled in FlexCAN settings!"
#endif
#if (CAN_TO_USE == FlexCan3) && (SPC5_CAN_USE_FLEXCAN3 == FALSE)
#error "Selected FlexCan3 device for printf but not enabled in FlexCAN settings!"
#endif
#if (CAN_TO_USE == FlexCan4) && (SPC5_CAN_USE_FLEXCAN4 == FALSE)
#error "Selected FlexCan4 device for printf but not enabled in FlexCAN settings!"
#endif
#if (CAN_TO_USE == FlexCan5) && (SPC5_CAN_USE_FLEXCAN5 == FALSE)
#error "Selected FlexCan5 device for printf but not enabled in FlexCAN settings!"
#endif

#define SPC5_IO_DEVICE_TYPE		SPC5_IO_DEVICE_CAN

#if (CAN_TO_USE == Sub0Can0)
#define SPC5_IO_DEVICE_NAME		"Sub0Can0"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&CAND1
#endif
#if (CAN_TO_USE == Sub0Can1)
#define SPC5_IO_DEVICE_NAME		"Sub0Can1"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&CAND2
#endif
#if (CAN_TO_USE == Sub0Can2)
#define SPC5_IO_DEVICE_NAME		"Sub0Can2"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&CAND3
#endif
#if (CAN_TO_USE == Sub0Can3)
#define SPC5_IO_DEVICE_NAME		"Sub0Can3"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&CAND4
#endif
#if (CAN_TO_USE == Sub1Can1)
#define SPC5_IO_DEVICE_NAME		"Sub1Can1"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&CAND7
#endif
#if (CAN_TO_USE == Sub1Can2)
#define SPC5_IO_DEVICE_NAME		"Sub1Can2"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&CAND8
#endif
#if (CAN_TO_USE == Sub1Can3)
#define SPC5_IO_DEVICE_NAME		"Sub1Can3"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&CAND9
#endif
#if (CAN_TO_USE == Sub1Can4)
#define SPC5_IO_DEVICE_NAME		"Sub1Can4"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&CAND10
#endif

#if (CAN_TO_USE == FlexCan0)
#define SPC5_IO_DEVICE_NAME		"FlexCan0"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&CAND1
#endif
#if (CAN_TO_USE == FlexCan1)
#define SPC5_IO_DEVICE_NAME		"FlexCan1"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&CAND2
#endif
#if (CAN_TO_USE == FlexCan2)
#define SPC5_IO_DEVICE_NAME		"FlexCan2"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&CAND3
#endif
#if (CAN_TO_USE == FlexCan3)
#define SPC5_IO_DEVICE_NAME		"FlexCan3"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&CAND4
#endif
#if (CAN_TO_USE == FlexCan4)
#define SPC5_IO_DEVICE_NAME		"FlexCan4"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&CAND5
#endif
#if (CAN_TO_USE == FlexCan5)
#define SPC5_IO_DEVICE_NAME		"FlexCan5"
#define SPC5_IO_DEVICE_ADDRESS	(uint32_t)&CAND6
#endif

#ifndef SPC5_IO_DEVICE_NAME
#error "Please fill the Device Set By User field (CAN Choice) with a correct device name to use as serial device!"
#endif

#define SPC5_FLEX_CAN			FALSE


#endif /* PRINTF_USE_CAN */

#endif /* _SPC5_IO_CFG_H_ */

/** @} */

