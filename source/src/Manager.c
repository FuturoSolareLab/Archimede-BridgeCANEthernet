/*
 * manager.c
 *
 *  Created on: 29 ago 2026
 *      Author: gabry
 */

#include "Manager.h"

uint16_t Pack_1_V;
uint16_t Pack_2_V;
uint16_t Pack_1_T;
uint16_t Pack_2_T;

int Battery_Check(){
	if(Cell_Vmax < 3.95 && Cell_Vmin > 2.00 && Pack_Tmax < 60) return 1;
	else return 0;
}

void Manager_task(void) {
	if (Battery_Check() == 1){

	}
	else{

	}
}
