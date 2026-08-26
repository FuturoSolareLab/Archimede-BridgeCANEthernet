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

#include "board.h"
#include "clock.h"

/*
 * Initial setup of MSCR_IO registers, the list is terminated
 * by a {-1, 0, 0}.
 */
static spc_mscr_io_init_t spc_mscr_io_init[] = {
  {(int16_t)MSCR_IO_PIN_TXD_0, (iomode_t)(PAL_SPC5_SSS(1) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_RXD_0, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(0) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE | PAL_SPC5_WPUE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_GPIO_clacson, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_GPIO_fendinebbia, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(0) | PAL_SPC5_ILS(0) | PAL_SPC5_IBE | PAL_SPC5_WPDE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_TX_0_0, (iomode_t)(PAL_SPC5_SSS(1) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_RX_0_0, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(0) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE | PAL_SPC5_WPUE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_GPIO_frecciaSX, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(0) | PAL_SPC5_ILS(0) | PAL_SPC5_IBE | PAL_SPC5_WPDE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_GPIO_anabbaglianteF, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(0) | PAL_SPC5_ILS(0) | PAL_SPC5_IBE | PAL_SPC5_WPDE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_GPIO_frecciaDX, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(0) | PAL_SPC5_ILS(0) | PAL_SPC5_IBE | PAL_SPC5_WPDE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_GPIO_posizione, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(0) | PAL_SPC5_ILS(0) | PAL_SPC5_IBE | PAL_SPC5_WPDE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_GPIO_anabbagliante, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(0) | PAL_SPC5_ILS(0) | PAL_SPC5_IBE | PAL_SPC5_WPDE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_GPIO_abbagliante, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {-1, 0, 0}
};

/*
 * Initial setup of MSCR_MUX registers, the list is terminated
 * by a {-1, 0}.
 */
static spc_mscr_mux_init_t spc_mscr_mux_init[] = {
  {(int16_t)(MSCR_MUX_PIN_RXD_0), 1U},
  {(int16_t)(MSCR_MUX_PIN_RX_0_0), 2U},
  {-1, 0}
};

/**
 * @brief   PAL setup.
 */
static PALConfig pal_default_config = {
  spc_mscr_io_init,
  spc_mscr_mux_init
};

/*
 * Board-specific initialization code.
 */
void boardInit(void) {

  pal_init(&pal_default_config);
}
