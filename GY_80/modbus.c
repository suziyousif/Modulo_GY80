/*
 * modbus.c
 *
 *  Created on: 6 de dez de 2018
 *      Author: Heloiza S. and Suzi Y.
 */

#include "../lib/avr_usart.h"
#include "ADXL345.h"
#include "modbus.h"

#include <util/delay.h>

void RTU_package(FILE *usart_stream, package_t *pkg, axis_t *data)
{

	uint8_t i;
	//uint8_t vetor[6] = {0x15, 0x01, 0x00, 0x05, 0x00, 0x04};
	for(i = 0; i < 3; i++){
		modbus_write(pkg, data->coordinate[i]);

		pkg->crc = CRC16_2(pkg->package, 6);
		pkg->data = convert_byte(pkg->data);
		pkg->reg = convert_byte(pkg->reg);

		USART_tx(pkg->addr);
		USART_tx(pkg->cmd);
		USART_tx((uint8_t)(pkg->reg >> 8));
		USART_tx((uint8_t)(pkg->reg));
		USART_tx((uint8_t)(pkg->data >> 8));
		USART_tx((uint8_t)(pkg->data));
		USART_tx((uint8_t)(pkg->crc >> 8));
		USART_tx((uint8_t)(pkg->crc));

		pkg->addr = USART_rx();
		pkg->cmd = USART_rx();
		pkg->reg = USART_rx();
		pkg->reg = (pkg->reg <<8) | USART_rx();
		pkg->data = USART_rx();
		pkg->data = (pkg->data <<8) | USART_rx();
		pkg->crc = USART_rx();
		pkg->crc = (pkg->crc <<8) | USART_rx();
		_delay_ms(100);
	}
}

void modbus_write(package_t *pkg, uint16_t data)
{
	pkg->addr = MODBUS_ADDRESS;
	pkg->cmd = MODBUS_WRITE;
	pkg->data = convert_byte(data);
	pkg->reg = convert_byte((uint16_t)MODBUS_REG_SENSOR0);
}

uint16_t CRC16_2(uint8_t *buf, int len)
{
	uint32_t crc = 0xFFFF;
	int i;

	for (i = 0; i < len; i++)
	{
	crc ^= (uint16_t)buf[i]; // XOR byte into least sig. byte of crc
		for (int i = 8; i != 0; i--) { // Loop over each bit
			if ((crc & 0x0001) != 0) { // If the LSB is set
				crc >>= 1; // Shift right and XOR 0xA001
				crc ^= 0xA001;
			}
			else // Else LSB is not set
				crc >>= 1; // Just shift right
		}
	}
	return crc;
}

uint16_t convert_byte(uint16_t data)
{
	uint16_t new_data, data_;
	new_data = data >>8;
	data_ = data <<8;
	new_data |= data_;
	return new_data;
}
