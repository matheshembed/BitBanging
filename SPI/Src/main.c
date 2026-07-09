#include <stdint.h>

#include "stm32f446xx.h"
#include "spi_bitbang.h"
#include "spi_protocol.h"
#include "delay.h"
#include "bmp280.h"

SPI_BB_Handle_t SPI;
//BMP280_Handle_t BMP;

//uint8_t txBuffer[4] = { 0xA5, 0x55, 0xF0, 0x0F };

//uint8_t rxBuffer[4];

int main(void) {
	/* SPI Configuration */

	SPI.GPIOx = GPIOA;

	SPI.SCLK_Pin = GPIO_PIN_NO_5;
	SPI.MOSI_Pin = GPIO_PIN_NO_7;
	SPI.MISO_Pin = GPIO_PIN_NO_6;
	SPI.CS_Pin = GPIO_PIN_NO_4;

	SPI_BB_Init(&SPI);

	volatile uint8_t txData = 0;
	volatile uint8_t rxData = 0;

	while (1) {

		SPI_BB_Select(&SPI);

		rxData = SPI_BB_TransferByte(&SPI, txData);

		SPI_BB_Deselect(&SPI);

		txData++;

		delay_ms(1000);
	}

	//BMP.hspi = &SPI;

	//BMP280_Init(&BMP);

	/*uint8_t chipID;

	 while (1) {
	 chipID = BMP280_ReadRegister(&BMP,BMP280_REG_CHIP_ID);

	 delay_ms(1000);
	 }
	 */

	//The below program is to test whether all the functions is working and getting reliable communication .. it can be verified using a logic analyzer

	/*    while(1)
	 {
	 ************************************************
	 * TEST 1 : TransferByte()
	 ************************************************

	 SPI_BB_Select(&SPI);

	 SPI_BB_TransferByte(&SPI,0xA5);

	 SPI_BB_Deselect(&SPI);

	 delay_ms(1000);


	 ************************************************
	 * TEST 2 : TransferBuffer()
	 ************************************************

	 SPI_BB_Select(&SPI);

	 SPI_BB_TransferBuffer(&SPI,txBuffer,rxBuffer,4);

	 SPI_BB_Deselect(&SPI);

	 delay_ms(1000);


	 ************************************************
	 * TEST 3 : Transmit()
	 ************************************************

	 SPI_BB_Transmit(&SPI,txBuffer,4);

	 delay_ms(1000);


	 ************************************************
	 * TEST 4 : Receive()
	 *
	 * Connect MOSI ----> MISO
	 ************************************************

	 SPI_BB_Receive(&SPI,rxBuffer,4);

	 delay_ms(1000);


	 ************************************************
	 * TEST 5 : TransmitReceive()
	 *
	 * Connect MOSI ----> MISO
	 ************************************************

	 SPI_BB_TransmitReceive(&SPI,txBuffer,rxBuffer,4);

	 delay_ms(3000);
	 }
	 */

}
