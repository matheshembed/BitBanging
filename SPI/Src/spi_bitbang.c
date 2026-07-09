/*
 * spi_bitbang.c
 *
 *  Created on: 07-Jul-2026
 *      Author: mathe
 */

#include "spi_bitbang.h"
#include "delay.h"

void SPI_BB_Init(SPI_BB_Handle_t *hspi) {
	GPIO_Handle_t GPIO_InitStruct;

	/* Enable GPIO Clock */
	GPIO_PeriClockControl(hspi->GPIOx, ENABLE);

	/* Common GPIO Configuration */
	GPIO_InitStruct.pGPIOx = hspi->GPIOx;
	GPIO_InitStruct.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_InitStruct.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIO_InitStruct.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	/************* SCLK *************/
	GPIO_InitStruct.GPIO_PinConfig.GPIO_PinNumber = hspi->SCLK_Pin;
	GPIO_InitStruct.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIO_Init(&GPIO_InitStruct);

	/************* MOSI *************/
	GPIO_InitStruct.GPIO_PinConfig.GPIO_PinNumber = hspi->MOSI_Pin;
	GPIO_InitStruct.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIO_Init(&GPIO_InitStruct);

	/************* MISO *************/
	GPIO_InitStruct.GPIO_PinConfig.GPIO_PinNumber = hspi->MISO_Pin;
	GPIO_InitStruct.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIO_Init(&GPIO_InitStruct);

	/************* CS *************/
	GPIO_InitStruct.GPIO_PinConfig.GPIO_PinNumber = hspi->CS_Pin;
	GPIO_InitStruct.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIO_Init(&GPIO_InitStruct);

	/* SPI Mode 0 Idle State */

	GPIO_WriteToOutputPin(hspi->GPIOx, hspi->CS_Pin, GPIO_PIN_SET);

	GPIO_WriteToOutputPin(hspi->GPIOx, hspi->SCLK_Pin, GPIO_PIN_RESET);

	GPIO_WriteToOutputPin(hspi->GPIOx, hspi->MOSI_Pin, GPIO_PIN_RESET);
}

/*************************************************/

void SPI_BB_Select(SPI_BB_Handle_t *hspi) {
	GPIO_WriteToOutputPin(hspi->GPIOx, hspi->CS_Pin, GPIO_PIN_RESET);

}

/*************************************************/

void SPI_BB_Deselect(SPI_BB_Handle_t *hspi) {
	GPIO_WriteToOutputPin(hspi->GPIOx, hspi->CS_Pin, GPIO_PIN_SET);
}

/*************************************************/

uint8_t SPI_BB_TransferBit(SPI_BB_Handle_t *hspi, uint8_t txBit) {
	uint8_t rxBit;

	/* Put data on MOSI */

	if (txBit) {
		GPIO_WriteToOutputPin(hspi->GPIOx, hspi->MOSI_Pin,
		GPIO_PIN_SET);
	} else {
		GPIO_WriteToOutputPin(hspi->GPIOx, hspi->MOSI_Pin,
		GPIO_PIN_RESET);
	}

	delay_us(5);

	/* Rising edge */

	GPIO_WriteToOutputPin(hspi->GPIOx, hspi->SCLK_Pin,
	GPIO_PIN_SET);

	/* Read MISO */

	rxBit = GPIO_ReadFromInputPin(hspi->GPIOx, hspi->MISO_Pin);

	delay_us(5);

	/* Falling edge */

	GPIO_WriteToOutputPin(hspi->GPIOx, hspi->SCLK_Pin,
	GPIO_PIN_RESET);

	return rxBit;
}

/************************************************************/

uint8_t SPI_BB_TransferByte(SPI_BB_Handle_t *hspi, uint8_t txData) {
	uint8_t rxData = 0;

	for (int8_t i = 7; i >= 0; i--) {
		uint8_t rxBit;

		rxBit = SPI_BB_TransferBit(hspi, (txData >> i) & 0x01);

		rxData |= (rxBit << i);
	}

	return rxData;
}

/**********************************************************************/

void SPI_BB_TransferBuffer(SPI_BB_Handle_t *hspi, uint8_t *txBuffer,uint8_t *rxBuffer, uint16_t length) {
	uint16_t i;
	uint8_t tx;
	uint8_t rx;

	for (i = 0; i < length; i++) {
		/* Default Dummy Byte */
		tx = 0xFF;

		if (txBuffer != NULL) {
			tx = txBuffer[i];
		}

		rx = SPI_BB_TransferByte(hspi, tx);

		if (rxBuffer != NULL) {
			rxBuffer[i] = rx;
		}
	}
}

/************************************************************************************/
void SPI_BB_Transmit(SPI_BB_Handle_t *hspi, uint8_t *txBuffer, uint16_t length) {
	SPI_BB_Select(hspi);

	SPI_BB_TransferBuffer(hspi, txBuffer,
	NULL, length);

	SPI_BB_Deselect(hspi);
}

/*************************************************************************************/

void SPI_BB_Receive(SPI_BB_Handle_t *hspi, uint8_t *rxBuffer, uint16_t length) {
	SPI_BB_Select(hspi);

	SPI_BB_TransferBuffer(hspi,
	NULL, rxBuffer, length);

	SPI_BB_Deselect(hspi);
}

/*****************************************************************************************/
void SPI_BB_TransmitReceive(SPI_BB_Handle_t *hspi, uint8_t *txBuffer,
		uint8_t *rxBuffer, uint16_t length) {
	SPI_BB_Select(hspi);

	SPI_BB_TransferBuffer(hspi, txBuffer, rxBuffer, length);

	SPI_BB_Deselect(hspi);
}
