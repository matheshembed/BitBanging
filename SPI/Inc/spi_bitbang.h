/*
 * spi_bitbang.h
 *
 *  Created on: 08-Jul-2026
 *      Author: mathe
 */

#ifndef SPI_BITBANG_H_
#define SPI_BITBANG_H_

#include <stdint.h>
#include "stm32f446xx.h"

/* SPI Bit Bang Handle */

typedef struct {
	GPIO_RegDef_t *GPIOx;

	uint8_t SCLK_Pin;
	uint8_t MOSI_Pin;
	uint8_t MISO_Pin;
	uint8_t CS_Pin;

} SPI_BB_Handle_t;

/* Initialization */

void SPI_BB_Init(SPI_BB_Handle_t *hspi);

/* Chip Select */

void SPI_BB_Select(SPI_BB_Handle_t *hspi);
void SPI_BB_Deselect(SPI_BB_Handle_t *hspi);

/* Low Level Transfer */

uint8_t SPI_BB_TransferBit(SPI_BB_Handle_t *hspi, uint8_t txBit);

uint8_t SPI_BB_TransferByte(SPI_BB_Handle_t *hspi, uint8_t txData);

void SPI_BB_TransferBuffer(SPI_BB_Handle_t *hspi, uint8_t *txBuffer,uint8_t *rxBuffer, uint16_t length);

/* High Level APIs */

void SPI_BB_Transmit(SPI_BB_Handle_t *hspi, uint8_t *txBuffer, uint16_t length);

void SPI_BB_Receive(SPI_BB_Handle_t *hspi, uint8_t *rxBuffer, uint16_t length);

void SPI_BB_TransmitReceive(SPI_BB_Handle_t *hspi, uint8_t *txBuffer,uint8_t *rxBuffer, uint16_t length);

#endif
