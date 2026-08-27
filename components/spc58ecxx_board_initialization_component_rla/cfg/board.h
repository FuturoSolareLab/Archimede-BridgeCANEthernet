/****************************************************************************
*
* Copyright © 2017-2019 STMicroelectronics - All Rights Reserved
*
* This software is licensed under SLA0098 terms that can be found in the
* DM00779817_1_0.pdf file in the licenses directory of this software product.
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
*****************************************************************************/

#ifndef _BOARD_H_
#define _BOARD_H_

#include "pal.h"

/*
 * Setup for a generic SPC58ECxx board.
 */

/*
 * Board identifiers.
 */
#define BOARD_GENERIC_SPC58ECXX
#define BOARD_NAME                  "Generic SPC58ECxx"

/*
 * Support macros.
 */
#define MSCR_IO_INDEX(port, pin)    (((port) * 16U) + (pin))

/*
 * I/O definitions.
 */
#define PIN_TXD_0                   12U
#define PIN_RXD_0                   13U
#define PIN_GPIO_clacson            14U
#define PIN_GPIO_fendinebbia        4U
#define PIN_TX_0_0                  14U
#define PIN_RX_0_0                  15U
#define PIN_GPIO_frecciaSX          6U
#define PIN_GPIO_abbaglianteF       7U
#define PIN_GPIO_frecciaDX          14U
#define PIN_GPIO_posizione          15U
#define PIN_GPIO_anabbagliante      13U
#define PIN_GPIO_abbagliante        14U

/*
 * PORT definitions.
 */
#define PORT_PIN_TXD_0              PORT_A
#define PORT_PIN_RXD_0              PORT_A
#define PORT_PIN_GPIO_clacson       PORT_A
#define PORT_PIN_GPIO_fendinebbia   PORT_A
#define PORT_PIN_TX_0_0             PORT_D
#define PORT_PIN_RX_0_0             PORT_D
#define PORT_PIN_GPIO_frecciaSX     PORT_D
#define PORT_PIN_GPIO_abbaglianteF  PORT_D
#define PORT_PIN_GPIO_frecciaDX     PORT_F
#define PORT_PIN_GPIO_posizione     PORT_F
#define PORT_PIN_GPIO_anabbagliante PORT_G
#define PORT_PIN_GPIO_abbagliante   PORT_M

/*
 * MSCR_IO definitions.
 */
#define MSCR_IO_PIN_TXD_0           MSCR_IO_INDEX(PORT_PIN_TXD_0, PIN_TXD_0)
#define MSCR_IO_PIN_RXD_0           MSCR_IO_INDEX(PORT_PIN_RXD_0, PIN_RXD_0)
#define MSCR_IO_PIN_GPIO_clacson    MSCR_IO_INDEX(PORT_PIN_GPIO_clacson, PIN_GPIO_clacson)
#define MSCR_IO_PIN_GPIO_fendinebbia MSCR_IO_INDEX(PORT_PIN_GPIO_fendinebbia, PIN_GPIO_fendinebbia)
#define MSCR_IO_PIN_TX_0_0          MSCR_IO_INDEX(PORT_PIN_TX_0_0, PIN_TX_0_0)
#define MSCR_IO_PIN_RX_0_0          MSCR_IO_INDEX(PORT_PIN_RX_0_0, PIN_RX_0_0)
#define MSCR_IO_PIN_GPIO_frecciaSX  MSCR_IO_INDEX(PORT_PIN_GPIO_frecciaSX, PIN_GPIO_frecciaSX)
#define MSCR_IO_PIN_GPIO_abbaglianteF MSCR_IO_INDEX(PORT_PIN_GPIO_abbaglianteF, PIN_GPIO_abbaglianteF)
#define MSCR_IO_PIN_GPIO_frecciaDX  MSCR_IO_INDEX(PORT_PIN_GPIO_frecciaDX, PIN_GPIO_frecciaDX)
#define MSCR_IO_PIN_GPIO_posizione  MSCR_IO_INDEX(PORT_PIN_GPIO_posizione, PIN_GPIO_posizione)
#define MSCR_IO_PIN_GPIO_anabbagliante MSCR_IO_INDEX(PORT_PIN_GPIO_anabbagliante, PIN_GPIO_anabbagliante)
#define MSCR_IO_PIN_GPIO_abbagliante MSCR_IO_INDEX(PORT_PIN_GPIO_abbagliante, PIN_GPIO_abbagliante)

/*
 * MSCR_MUX definitions.
 */
#define MSCR_MUX_PIN_RXD_0          336U
#define MSCR_MUX_PIN_RX_0_0         245U

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
