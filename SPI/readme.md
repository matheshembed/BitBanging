# Software SPI (Bit-Banging) Driver for STM32F446RE

A bare-metal Software SPI (Bit-Banging) Master driver developed for the STM32F446RE using a custom GPIO driver. The project does not use the STM32 hardware SPI peripheral or HAL SPI library.

## Features

- Bare-metal register-level GPIO driver
- Software SPI (Bit-Banging) Master
- SPI Mode 0 (CPOL = 0, CPHA = 0)
- Bit and byte transfer
- Buffer transfer
- Transmit
- Receive
- Full-duplex transmit/receive

## Project Structure

```text
Inc/
├── stm32f446xx.h
├── stm32f446xx_gpio_driver.h
├── spi_bitbang.h
├── bmp280.h
└── spi_protocol.h

Src/
├── stm32f446xx_gpio_driver.c
├── spi_bitbang.c
├── bmp280.c
├── spi_protocol.c
└── main.c
```

## Validation

### Logic Analyzer
- Verified SPI clock generation
- Verified MOSI, MISO and CS timing
- Verified SPI Mode 0 operation

### BMP280
- Successfully communicated with the BMP280 over SPI
- Read and verified the Chip ID (`0x58`)

### STM32 ↔ Arduino Uno
- STM32F446RE configured as a **Software SPI Master**
- Arduino Uno configured as a **Hardware SPI Slave**
- Verified full-duplex communication by simultaneously transmitting and receiving data between both microcontrollers

## Hardware Used

- STM32 Nucleo-F446RE
- Arduino Uno
- BMP280 SPI Module
- Logic Analyzer
- Logic Level Shifter (3.3V ↔ 5V)

## Learning Outcomes

- Register-level GPIO programming
- Software implementation of the SPI protocol
- SPI timing and clock generation
- Full-duplex SPI communication
- SPI sensor interfacing
- Microcontroller-to-microcontroller communication

## Note

This project uses a custom bare-metal GPIO driver developed from scratch. The SPI protocol is implemented entirely in software without using the STM32 hardware SPI peripheral or HAL SPI APIs.