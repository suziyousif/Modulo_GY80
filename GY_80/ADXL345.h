/*
 * ADXL345.h
 *
 *  Created on: 3 de dez de 2018
 *      Author: Heloiza S. and Suzi Y.
 */

#ifndef GY_80_ADXL345_H_
#define GY_80_ADXL345_H_

#define ADXL345_ADDRESS 0x1D
#define ADXL345_ADDRESS_WRITE 0x3A
#define ADXL345_ADDRESS_READ 0x3B
#define AXIS_ADDRESS 0x32
#define AXIS_OFF_ADDRESS 0x1E

typedef struct
{
	uint16_t x;
	uint16_t y;
	uint16_t z;
}axis_t;



#endif /* GY_80_ADXL345_H_ */
