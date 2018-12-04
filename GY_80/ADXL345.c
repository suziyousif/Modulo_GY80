/*
 * ADXL345.c
 *
 *  Created on: 3 de dez de 2018
 *      Author: Heloiza S. and Suzi Y.
 */

#include "ADXL345.h"
#include "../lib/avr_twi_master.h"

uint8_t buffer[10];
void Multiple_Byte_Read(axis_t *axis){
	buffer[0] = ADXL345_ADDRESS_WRITE;
	buffer[1] = AXIS_ADDRESS;
	TWI_Start_Transceiver_With_Data(buffer, 2);
	buffer[0] = ADXL345_ADDRESS_READ;
	TWI_Start_Transceiver_With_Data(buffer, 7);
	TWI_Get_Data_From_Transceiver(buffer, 7);
	axis->x = *(uint16_t*) &buffer[1];
	axis->y = *(uint16_t*) &buffer[3];
	axis->z = *(uint16_t*) &buffer[5];

	/*Axis Offset*/
	buffer[0] = ADXL345_ADDRESS_WRITE;
	buffer[1] = AXIS_OFF_ADDRESS;
	TWI_Start_Transceiver_With_Data(buffer, 2);
	buffer[0] = ADXL345_ADDRESS_READ;
	TWI_Start_Transceiver_With_Data(buffer, 4);
	TWI_Get_Data_From_Transceiver(buffer, 4);
	axis->x = (uint32_t)(((axis->x)-buffer[1])*3900)/1000000;
	axis->y = (uint32_t)((axis->y)-buffer[2]*3900)/1000000;
	axis->z = (uint32_t)((axis->z)-buffer[3]*3900)/1000000;
}



