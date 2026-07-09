/*
 * bmp280.c
 *
 *  Created on: 08-Jul-2026
 *      Author: mathe
 */

#include "bmp280.h"

/**************************************************************/

void BMP280_Init(BMP280_Handle_t *hbmp)
{
    /* Reserved for future configuration */
}

/**************************************************************/

uint8_t BMP280_ReadRegister(BMP280_Handle_t *hbmp,uint8_t reg)
{
    uint8_t value;

    SPI_BB_Select(hbmp->hspi);

    SPI_BB_TransferByte(hbmp->hspi, reg | 0x80);

    value = SPI_BB_TransferByte(hbmp->hspi, 0xFF);

    SPI_BB_Deselect(hbmp->hspi);

    return value;
}

/**************************************************************/

void BMP280_WriteRegister(BMP280_Handle_t *hbmp,uint8_t reg,uint8_t value)
{
    SPI_BB_Select(hbmp->hspi);

    SPI_BB_TransferByte(hbmp->hspi, reg & 0x7F);

    SPI_BB_TransferByte(hbmp->hspi, value);

    SPI_BB_Deselect(hbmp->hspi);
}

/**************************************************************/

void BMP280_ReadRegisters(BMP280_Handle_t *hbmp,uint8_t reg,uint8_t *buffer,uint16_t length)
{
    uint16_t i;

    SPI_BB_Select(hbmp->hspi);

    SPI_BB_TransferByte(hbmp->hspi, reg | 0x80);

    for(i = 0; i < length; i++)
    {
        buffer[i] = SPI_BB_TransferByte(hbmp->hspi, 0xFF);
    }

    SPI_BB_Deselect(hbmp->hspi);
}
