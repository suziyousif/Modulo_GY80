/*
 * main_gy80.c
 *
 *  Created on: 4 de dez de 2018
 *      Author: Suzi and Heloiza
 */

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "GY_80/ADXL345.h"
#include "lib/avr_usart.h"
#include "lib/avr_twi_master.h"

int main(){
	FILE *usart_stream = get_usart_stream();

	/* Debug */
	USART_Init(B9600);
	axis_t axis;

	/* Inicializa modo líder */
	TWI_Master_Initialise();
	adxl345_init();
	sei();

	for(;;) {
		Multiple_Byte_Read(&axis, usart_stream);
		fprintf(usart_stream, "X = %d, Y = %d, Z = %d\n\r", axis.x, axis.y, axis.z);
		//print_axis(&axis, usart_stream);
		_delay_ms(1000);
	}

}
