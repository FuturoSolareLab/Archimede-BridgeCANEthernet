/*
 * LightControl.c
 *
 *  Created on: 28 ago 2025
 *      Author: Casa
 */

#include "LightControl.h"
#include "LightControl_cfg.h"

/**
 * @brief  Checks if the Light Control device is ready for operation.
 *
 * This function evaluates the internal state of the Light Control module
 * and returns whether it is in a ready condition (e.g., initialized and running).
 *
 */
void ReadStateLight(void){

	if(siul_lld_readpad(PORT_PIN_GPIO_anabbagliante, PIN_GPIO_anabbagliante) == 1) GPIORXBuffer |= (1 << anabbagliante);
	else GPIORXBuffer &= ~(1 << anabbagliante);

	if(siul_lld_readpad(PORT_PIN_GPIO_posizione, PIN_GPIO_posizione) == 1) GPIORXBuffer |= (1 << posizione);
	else GPIORXBuffer &= ~(1 << posizione);

	if(siul_lld_readpad(PORT_PIN_GPIO_frecciaSX, PIN_GPIO_frecciaSX) == 1) GPIORXBuffer |= (1 << frecciaSX);
	else GPIORXBuffer &= ~(1 << frecciaSX);

	if(siul_lld_readpad(PORT_PIN_GPIO_frecciaDX, PIN_GPIO_frecciaDX) == 1) GPIORXBuffer |= (1 << frecciaDX);
	else GPIORXBuffer &= ~(1 << frecciaDX);

	if(siul_lld_readpad(PORT_PIN_GPIO_abbagliante, PIN_GPIO_abbagliante) == 1) GPIORXBuffer |= (1 << abbagliante);
	else GPIORXBuffer &= ~(1 << abbagliante);

//	if(siul_lld_readpad(PORT_PIN_GPIO_retro, PIN_GPIO_retro) == 1) GPIORXBuffer |= (1 << retro);
//	else GPIORXBuffer &= ~(1 << retro);

	if(siul_lld_readpad(PORT_PIN_GPIO_stop, PIN_GPIO_stop) == 1) GPIORXBuffer |= (1 << stop);
	else GPIORXBuffer &= ~(1 << stop);
}

/**
 * @brief  Creates a CAN message containing all the required information
 *         for the specific module.
 *
 * @param[out] msg   Pointer to the CAN message structure to be filled.
 * @return void
 */
CANTxFrame* LightControl_GetStatus(void){

	static CANTxFrame tmp_BufferTx;

	ReadStateLight();	// Update state of variables

	//inizializzazione proprietà buffer
	tmp_BufferTx.ID = CAN_ID_LIGHTCONTROL;
	tmp_BufferTx.DLC = CAN_DLC_LIGHTCONTROL;
	tmp_BufferTx.OPERATION = CAN_OP_NORMAL;
	tmp_BufferTx.IDE = CAN_ID_STD;

	//inizializzazione messaggio
//	tmp_BufferTx.data8[0] = posizione;
//	tmp_BufferTx.data8[1] = frecciaDX;
//	tmp_BufferTx.data8[2] = frecciaSX;
//	tmp_BufferTx.data8[3] = anabbagliante;
//	tmp_BufferTx.data8[4] = abbagliante + abbaglianteF;
//	tmp_BufferTx.data8[5] = fendinebbia;
//	tmp_BufferTx.data8[6] = stop;

	tmp_BufferTx.data8[0] = GPIORXBuffer;

	return &tmp_BufferTx;
}


