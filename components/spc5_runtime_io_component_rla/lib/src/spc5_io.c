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

/*lint -save -e* */
#include <stdio.h>
#include <string.h>

#include <spc5_io.h>
#include <spc5_io_cfg.h>

#if PRINTF_USE_SERIAL
#include <serial_lld.h>
#elif PRINTF_USE_CAN
#include <can_lld_cfg.h>
#include <osal.h>

#define MAX_OUT_BUF 8U
#endif


#if (PRINTF_USE_NONE == FALSE)


#if PRINTF_USE_SERIAL
/**
 * @brief   Structure for serial communication port configuration.
 *
 */
extern SerialConfig serial_config_runtime_io; 
#endif  /* SERIAL */

/**
 * @brief   Structure containing informations of the selected device on which the stdout will be redirected.
 *
 */
io_devices_t io_device = {
		SPC5_IO_DEVICE_NAME,
		SPC5_IO_DEVICE_ADDRESS,
		SPC5_IO_DEVICE_TYPE
};
#endif

/**
 * @brief   Runtime IO module initialization.
 *
 * @api
 */
#ifdef __ghs__
#pragma ghs ZO
#endif
void ioInit(void) {

#if (PRINTF_USE_NONE == FALSE)
	FILE *new_stdout;
	FILE *new_stderr;
	FILE *new_stdin;

	new_stdout = freopen(io_device.name, "w", stdout);	/* Bind stdout stream with the chosen device.	*/
	if (new_stdout)	{									/* To avoid buffering when calling printf,	*/
		setvbuf(new_stdout, NULL, _IONBF, 0);			/* so it doesn't need to call fflush()		*/
	}													/* after calling printf.					*/

	new_stderr = freopen(io_device.name, "w", stderr);
	if (new_stderr)	{
		setvbuf(new_stderr, NULL, _IONBF, 0);
	}

	new_stdin = freopen(io_device.name, "r", stdin);
	if (new_stdin) {
		setvbuf(new_stdin, NULL, _IONBF, 0);
	}
#endif
}
#ifdef __ghs__
#pragma ghs O
#endif

/**
 * @brief   Runtime IO open device.
 *
 * @api
 */
int ioOpen(const char *pathname, int flags) {

	int io_id = 0;

	(void) flags;

#if (PRINTF_USE_NONE == FALSE)
	if (strcmp(io_device.name, pathname) == 0) {
		if ((io_device.flags & SPC5_IO_DEVICE_OPEN) == 0U ) {
			io_device.flags |= SPC5_IO_DEVICE_OPEN;

#if PRINTF_USE_SERIAL
			sd_lld_start((SerialDriver *)io_device.address, &serial_config_runtime_io);
#elif PRINTF_USE_CAN
			can_lld_start((CANDriver *)io_device.address, &SPC5_CAN_CONFIG);
#else
			io_id = -1;
#endif
		}
	} else {
		io_id = -1;
	}
#else
	(void) pathname;
#endif /* PRINTF_USE_NONE */

	return io_id;
}

/**
 * @brief   Runtime IO read buffer.
 *
 * @api
 */
uint16_t ioRead(int fd, void *buf, size_t count) {

	uint16_t len = 0;

	if (fd != 0)
		return -1;

#if PRINTF_USE_SERIAL
	len = sd_lld_read((SerialDriver *)io_device.address, buf, count);
#else
	(void) buf;
	(void) count;
#endif

	return len;
}

/**
 * @brief   Runtime IO write buffer.
 *
 * @api
 */
uint16_t ioWrite(int fd, const void *buf, size_t count) {

	if (fd != 0)
		return -1;

#if (PRINTF_USE_NONE == FALSE)
#if PRINTF_USE_SERIAL
	sd_lld_write((SerialDriver *)io_device.address, (uint8_t *)buf, count);
#elif PRINTF_USE_CAN
	uint8_t *p = (uint8_t *)buf;
	uint8_t *pData32;
	uint32_t bytes_to_send = count;
	uint32_t i;
	CANTxFrame txf;
	CANDriver *canp = (CANDriver *)io_device.address;

#if SPC5_FLEX_CAN
	txf.RTR = CAN_RTR_DATA;
	txf.LENGTH = MAX_OUT_BUF;
	if (canp->config->id_filter[0].scale == 0) { /* Check for frame format: 0=Standard, 1=Extended */
		txf.IDE = CAN_IDE_STD;
		txf.SID = canp->config->id_filter[0].register1; /* Take the Standard ID Mode Filter from configuration. */
	}
	else {
		txf.IDE = CAN_IDE_EXT;
		txf.EID = canp->config->id_filter[0].register1; /* Take the Extended ID Mode Filter from configuration. */
	}

#else
	if (canp->config->numof_std_filters != 0) { /* Check for Standard Filter */
		txf.TYPE = CAN_ID_STD;
		txf.ID = canp->config->STD_Filter[0].SFID1; /* Take the Standard Filter value 1 from configuration. */
	}
	if (canp->config->numof_xtd_filters != 0) { /* Check for Extended Filter */
		txf.TYPE = CAN_ID_XTD;
		txf.ID = canp->config->XTD_Filter[0].EFID1; /* Take the Extended Filter value 1 from configuration. */
	}
	txf.DLC = MAX_OUT_BUF;
#endif

	while (bytes_to_send > MAX_OUT_BUF) {
		pData32 = (uint8_t *)txf.data32;
		for(i = 0; i < MAX_OUT_BUF; i++)
			*pData32++ = *p++;

#if SPC5_FLEX_CAN
		can_lld_transmit(canp, CAN_ANY_MAILBOX, &txf);
#else
		can_lld_transmit(canp, CAN_ANY_TXBUFFER, &txf);
#endif
		osalThreadDelayMilliseconds(10);

		bytes_to_send -= MAX_OUT_BUF;
	}

	pData32 = (uint8_t *)txf.data32;
	for(i = 0; i < bytes_to_send; i++)
		*pData32++ = *p++;

	for(i = 0; i < (MAX_OUT_BUF - bytes_to_send); i++)
		*pData32++ = '\0';

#if SPC5_FLEX_CAN
	can_lld_transmit(canp, CAN_ANY_MAILBOX, &txf);
#else
	can_lld_transmit(canp, CAN_ANY_TXBUFFER, &txf);
#endif
#endif /* PRINTF_USE_SERIAL */
#else
	(void) buf;
#endif /* PRINTF_USE_NONE */

	return (uint16_t)count;
}
/*lint -restore */
