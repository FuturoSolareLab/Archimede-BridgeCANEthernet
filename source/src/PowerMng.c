/*
 * PowerMng.c
 *
 *  Created on: 4 set 2026
 *      Author: Casa
 */

#include "PowerMng.h"
#include "PowerMng_cfg.h"
#include "can_hal.h"


uint16_t Voltage_Battery_1;
uint16_t Voltage_Battery_2;
uint16_t Voltage_VBus;

uint16_t Current_Battery_1;
uint16_t Current_Battery_2;
uint16_t Current_MPPT;

bool Status_SW_RelPreCharge;
bool Status_SW_RelPower;

uint16_t VoltageDiff;

bool Sts_RelePreCharge_1 = FALSE;
bool Sts_RelePreCharge_2 = FALSE;
bool Sts_RelePower_1 = FALSE;
bool Sts_RelePower_2 = FALSE;

bool Sts_FaulRelePower = FALSE; // False NO FAULT

Macchine_Sts_e Macchine_Sts = Mng_Init;

CAN_Frame CAN_FrPower = {
    .id   = CAN_ID_RELSTS,
    .dlc  = CAN_DLC_RELST,
    .data = {0}
};


void Read_InputAction(void){
	/* Leggiamo lo stato dei pin in Ingresso */
	Status_SW_RelPreCharge = siul_lld_readpad(PORT_InRelPreCharge, InRelPreCharge);
	Status_SW_RelPower = siul_lld_readpad(PORT_InRelPower, InRelPower);
}

void Set_Rele(void){
	siul_lld_writepad(PORT_OutRelPreCha1, OutRelPreCha1, Sts_RelePreCharge_1);
	siul_lld_writepad(PORT_OutRelPreCha2, OutRelPreCha2, Sts_RelePreCharge_2);
	siul_lld_writepad(PORT_OutRelPower1, OutRelPower1, Sts_RelePower_1);
	siul_lld_writepad(PORT_OutRelPower2, OutRelPower2, Sts_RelePower_2);

	// Costruiamo il Frame e lo inviamo
	CAN_FrPower.data[0] = (uint8_t)(
		      ((Sts_RelePreCharge_1 & 0x01U) << CAN_POS_RELPRECHARGE1) |
		      ((Sts_RelePreCharge_2 & 0x01U) << CAN_POS_RELPRECHARGE2) |
		      ((Sts_RelePower_1     & 0x01U) << CAN_POS_RELPOWER1)     |
		      ((Sts_RelePower_2     & 0x01U) << CAN_POS_RELPOWER2));

	CAN_Send(&CAN_FrPower);
}

void PowerMng(void){
	Read_InputAction();

	switch(Macchine_Sts)
	{
	/* Accensione del sistema e verifica che il pacco batteria sia ok.
	 * Che le tensioni delle batterie siano dentro i limiti
	 * In questo modo aspettiamo anche che il sistema si accendi */
	case Mng_Init:
		if((Voltage_Battery_1 > MIN_BATTERY_VALUE) && (Voltage_Battery_2 > MIN_BATTERY_VALUE) &&
				(Voltage_Battery_1 < MAX_BATTERY_VALUE) && (Voltage_Battery_2 < MAX_BATTERY_VALUE))
		{
			Macchine_Sts = Mng_PreOperation;
		}
		break;
	/* Inziamo ad alimentare il veicolo attivando il PreCharge. Aspettiamo che il sistema arrivi a regime  */
	case Mng_PreOperation:
		// Se il Bus è basso di tensione accendo devo accendere i relè di PreCharge
		if(Voltage_VBus < VBUS_LOW_VALUE) {
			/* Attivazione dei rele */
			if((Status_SW_RelPreCharge == TRUE) && (!Sts_FaulRelePower))
			{
				Sts_RelePreCharge_1 = Sts_RelePreCharge_2 = TRUE;
				Set_Rele();
			} else {
				Sts_RelePreCharge_1 = Sts_RelePreCharge_2 = FALSE;
				Set_Rele();
			}
		// Se il Vbus ha superato la soglia del VBUS_LOW_VALUE, vuol dire che si è un pò caricato
		} else {
			// Calcoliamo al differenza di tensione tra le due Batterie prima di attivare il relè di potenza
			uint16_t Batt_diff = (Voltage_Battery_1 >= Voltage_Battery_2) ? (Voltage_Battery_1 - Voltage_Battery_2) : (Voltage_Battery_2 - Voltage_Battery_1);
			// Calcoliamo la differenza tra Vbus e la batteria più carica
			uint16_t Vbus_diff = (Voltage_Battery_1 >= Voltage_Battery_2) ? (Voltage_Battery_1 - Voltage_VBus) : (Voltage_Battery_2 - Voltage_VBus);

			// Se la differenza è accetabile passa in operation dove è possibile attivare i relè di potenza
			if((Batt_diff < MAX_DELTA_V_BATTERY_PRESTS) && (Vbus_diff < MAX_DELTA_V_VBUS_BATTERY_PRESTS)) {
				Macchine_Sts = Mng_Operation;
				break;
			}
		}
		break;
	case Mng_Operation:
		// Se lo SW è ON
		if(Status_SW_RelPower)
		{
			/* Se lo SW OP è ON:
			 * 		Attiva il relè con la minor differenza di tensione tra Vbus e Batt
			 * 		Fai il check che la tensione tra le due batterie sia minore del MAX_DELTA_V_BATTERY_OPSTS Attiva anche l'altro relè Power
			 * 		Attiva il Relè dei pannelli solari
			 */

		}

		break;
	}

	Set_Rele();

}
