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
 * @file    spc5_io.h
 * @brief   SPC5 Runtime I/O file.
 */

#ifndef _SPC5_IO_H_
#define _SPC5_IO_H_

#include <typedefs.h>
#include <stdio.h>
#include <spc5_io_cfg.h>

/*lint -save -e* */
#ifndef __ghs__
#ifdef HIGHTEC_PRO
#include <types.h>
#include <stat.h>
#define ssize_t _ssize_t
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif
#endif
/*lint restore */

/**
 * @brief   Structure representing the available io devices.
 */
typedef struct io_devices_s {
/**
 * @brief   Device name.
 */
	char name[16];
/**
 * @brief   Pointer to the specific device driver structure.
 */
	uint32_t address;
/**
 * @brief   I/O devices flag bit fields:
 *          bit[0,7]   -> Used device
 *          bit[8,15]  -> Device type
 *          bit[16,23] -> Device status
 *
 */
	uint32_t flags;
} io_devices_t;

/*
 * I/O devices flag bit fields:
 *
 * 0       7 8     15 16    23
 * +--------+--------+--------+
 * | device | type   | status |
 * +--------+--------+--------+
 *
 */

/**
 * @name    IO_Runtime macro definitions
 * @{
 */
#define SPC5_IO_DEVICE_MASK       0x000000FFUL

#define SPC5_IO_DEVICE_SERIAL     (1UL << 0)
#define SPC5_IO_DEVICE_CAN        (1UL << 1)
#define SPC5_IO_DEVICE_ETHERNET   (1UL << 2)

#define SPC5_IO_DEVICE_STDIN      (1UL << 8)
#define SPC5_IO_DEVICE_STDOUT     (1UL << 9)
#define SPC5_IO_DEVICE_STDERR     (1UL << 10)

#define SPC5_IO_DEVICE_OPEN       (1UL << 16)
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/
extern io_devices_t io_device;

#ifdef __cplusplus
extern "C" {
#endif
extern void ioInit(void);
extern int ioOpen(const char *pathname, int flags);
extern uint16_t ioRead(int fd, void *buf, size_t count);
extern uint16_t ioWrite(int fd, const void *buf, size_t count);
#ifdef __cplusplus
}
#endif

#endif /* _SPC5_IO_H_ */
