/*
 * ADXL345.c
 *
 *  Created on: 3 de dez de 2018
 *      Author: Heloiza S. and Suzi Y.
 */


#include "ADXL345.h"
#include "../lib/avr_twi_master.h"

uint8_t buffer[10]={0};

void adxl345_init(){
	buffer[0] = ADXL345_ADDRESS_WRITE;
	buffer[1] = POWER_CTL;
	buffer[2] = MEASURE_ENABLE;
	TWI_Start_Transceiver_With_Data(buffer, 3);
}

void Multiple_Byte_Read(axis_t *axis, FILE *file){
	buffer[0] = ADXL345_ADDRESS_WRITE;
	buffer[1] = AXIS_ADDRESS;
	TWI_Start_Transceiver_With_Data(buffer, 2);
	buffer[0] = ADXL345_ADDRESS_READ;
	TWI_Start_Transceiver_With_Data(buffer, 7);
	TWI_Get_Data_From_Transceiver(buffer, 7);
	axis->x = *(int16_t*) &buffer[1];
	axis->y = *(int16_t*) &buffer[3];
	axis->z = *(int16_t*) &buffer[5];

	/*Axis Offset*/
	buffer[0] = ADXL345_ADDRESS_WRITE;
	buffer[1] = AXIS_OFF_ADDRESS;
	TWI_Start_Transceiver_With_Data(buffer, 2);
	buffer[0] = ADXL345_ADDRESS_READ;
	TWI_Start_Transceiver_With_Data(buffer, 4);
	TWI_Get_Data_From_Transceiver(buffer, 4);
	axis->x = (int32_t)((axis->x)-buffer[1])*1000/256;
	axis->y = (int32_t)((axis->y)-buffer[2])*1000/256;
	axis->z = (int32_t)((axis->z)-buffer[3])*1000/256;
}

void print_axis(axis_t *axis, FILE *file){
	fprintf(file,"x= %d, y=%d, z=%d\n\r",
			axis->x, axis->y, axis->z);
}



