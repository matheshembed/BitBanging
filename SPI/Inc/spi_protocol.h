/*
 * spi_protocol.h
 *
 *  Created on: 09-Jul-2026
 *      Author: mathe
 */

#ifndef SPI_PROTOCOL_H_
#define SPI_PROTOCOL_H_

#include <stdint.h>
#include "spi_bitbang.h"

/* Commands */

#define CMD_LED_ON         0x01
#define CMD_LED_OFF        0x02
#define CMD_LED_TOGGLE     0x03
#define CMD_ECHO           0x04
#define CMD_READ_ADC       0x05
#define CMD_READ_BUTTON    0x06

/* APIs */

void SPI_SendCommand(SPI_BB_Handle_t *hspi, uint8_t cmd);

uint8_t SPI_SendCommandReceive(SPI_BB_Handle_t *hspi, uint8_t cmd);

uint8_t SPI_Echo(SPI_BB_Handle_t *hspi, uint8_t data);

void SPI_LED_On(SPI_BB_Handle_t *hspi);
void SPI_LED_Off(SPI_BB_Handle_t *hspi);
void SPI_LED_Toggle(SPI_BB_Handle_t *hspi);

#endif /* SPI_PROTOCOL_H_ */
