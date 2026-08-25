/*
 * solo_drive_cfg.h
 *
 *  Created on: 18 gen 2026
 *      Author: Casa
 */

#ifndef CFG_SOLO_DRIVE_CFG_H_
#define CFG_SOLO_DRIVE_CFG_H_

typedef enum{
	SDO_VBUS = 0,
	SDO_SPEED,
	SDO_TEMP
};

#define TPDO_DELAY_SYNC  0x01 // Dopo quanti Sync viene mandato questo messaggio

#define NODE_1_ID 1
#define NODE_2_ID 2

/* ID dei TPDO dei Driver */
#define TPDO1_CAN_ID_BASE_1 0x281
#define TPDO2_CAN_ID_BASE_1 0x282
#define TPDO3_CAN_ID_BASE_1 0x283
#define TPDO4_CAN_ID_BASE_1 0x284
#define TPDO5_CAN_ID_BASE_1 0x285
#define TPDO6_CAN_ID_BASE_1 0x286

#define TPDO1_CAN_ID_BASE_2 0x291
#define TPDO2_CAN_ID_BASE_2 0x292
#define TPDO3_CAN_ID_BASE_2 0x293
#define TPDO4_CAN_ID_BASE_2 0x294
#define TPDO5_CAN_ID_BASE_2 0x295
#define TPDO6_CAN_ID_BASE_2 0x296





#define IDX_HEARTBEAT   0x1017
#define IDX_MODE        0x6060
#define IDX_CONTROLWORD 0x6040
#define IDX_TORQUE      0x3004

/* SOLO telemetry objects */
#define IDX_BUS_VOLT 0x3031
#define IDX_IQ       0x3034
#define IDX_ID       0x3035
#define IDX_SPEED    0x3036
#define IDX_TEMP     0x3039


#define TPDO_DISABLE 	0x01
#define TPDO_ACTIVE		0x02

/* PDO MAP */
#define TPDO2_MAP  0x1A15
#define TPDO3_MAP  0x1A16
#define TPDO4_MAP  0x1A17
#define TPDO6_MAP  0x1A19

#endif /* CFG_SOLO_DRIVE_CFG_H_ */
