/*
 * Serial.h
 *
 *  Created on: 24 ago 2026
 *      Author: Casa
 */

#ifndef INC_SERIAL_H_
#define INC_SERIAL_H_

void Serial_RX_msg(void);
void Serial_TX_msg(uint32_t CAN_id, uint8_t DLC, uint32_t *CAN_data);

#endif /* INC_SERIAL_H_ */
