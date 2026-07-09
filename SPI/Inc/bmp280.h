/*
 * bmp280.h
 *
 *  Created on: 08-Jul-2026
 *      Author: mathe
 */

#ifndef BMP280_H_
#define BMP280_H_

#include <stdint.h>
#include "spi_bitbang.h"

/******************************************************************
 * BMP280 Registers
 ******************************************************************/

#define BMP280_REG_CHIP_ID        0xD0
#define BMP280_REG_RESET          0xE0
#define BMP280_REG_STATUS         0xF3
#define BMP280_REG_CTRL_MEAS      0xF4
#define BMP280_REG_CONFIG         0xF5

#define BMP280_REG_PRESS_MSB      0xF7
#define BMP280_REG_PRESS_LSB      0xF8
#define BMP280_REG_PRESS_XLSB     0xF9

#define BMP280_REG_TEMP_MSB       0xFA
#define BMP280_REG_TEMP_LSB       0xFB
#define BMP280_REG_TEMP_XLSB      0xFC

/******************************************************************
 * BMP280 Handle
 ******************************************************************/

typedef struct
{
    SPI_BB_Handle_t *hspi;

}BMP280_Handle_t;

/******************************************************************
 * Public APIs
 ******************************************************************/

void BMP280_Init(BMP280_Handle_t *hbmp);

uint8_t BMP280_ReadRegister(BMP280_Handle_t *hbmp,uint8_t reg);

void BMP280_WriteRegister(BMP280_Handle_t *hbmp,uint8_t reg,uint8_t value);

void BMP280_ReadRegisters(BMP280_Handle_t *hbmp,uint8_t reg,uint8_t *buffer,uint16_t length);

#endif
