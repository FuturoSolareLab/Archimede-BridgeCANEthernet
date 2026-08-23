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
/**
 * @file    spc5_io_cfg.h
 * @brief   SPC5 Runtime I/O configuration file.
 *
 * @addtogroup SPC5_RUNTIME_IO
 * @{
 */

#include "spc5_io_cfg.h"

#if PRINTF_USE_SERIAL
#include <serial_lld.h>
#endif

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/


#if (PRINTF_USE_SERIAL == TRUE)

/**
 * @brief   Structure defining the SERIAL configuration for runtime IO - API mode : SYNCHRONOUS".
 */


SerialConfig serial_config_runtime_io = {
  38400,
  SD_MODE_8BITS_PARITY_NONE,
  SPC5_LIN_API_MODE_SYNCHRONOUS,
  NULL,
  NULL,
  FALSE,
  NULL,
  0,
  NULL 
};

#endif
/*===========================================================================*/
/* Driver local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/


/** @} */
