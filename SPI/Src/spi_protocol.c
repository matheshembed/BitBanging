/*
 * spi_protocol.c
 *
 *  Created on: 09-Jul-2026
 *      Author: mathe
 */


/*
 * spi_protocol.c
 */

#include "spi_protocol.h"
#include "spi_bitbang.h"

/****************************************************/

void SPI_SendCommand(SPI_BB_Handle_t *hspi,uint8_t cmd)
{
    SPI_BB_Select(hspi);

    SPI_BB_TransferByte(hspi, cmd);

    SPI_BB_Deselect(hspi);
}

/****************************************************/

uint8_t SPI_SendCommandReceive(SPI_BB_Handle_t *hspi,uint8_t cmd)
{
    uint8_t rx;

    SPI_BB_Select(hspi);

    rx = SPI_BB_TransferByte(hspi, cmd);

    SPI_BB_Deselect(hspi);

    return rx;
}

/****************************************************/

uint8_t SPI_Echo(SPI_BB_Handle_t *hspi,uint8_t data)
{
    uint8_t rx;

    SPI_BB_Select(hspi);

    SPI_BB_TransferByte(hspi, CMD_ECHO);

    rx = SPI_BB_TransferByte(hspi, data);

    SPI_BB_Deselect(hspi);

    return rx;
}


