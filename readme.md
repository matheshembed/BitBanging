# Bit Banging

Software implementation of communication protocols using **GPIO bit banging** without relying on dedicated hardware peripherals.

This repository focuses on understanding serial communication protocols from the firmware level by manually generating protocol timing, frame structures, and bus transactions using software.

The objective is to develop production-style embedded drivers while gaining a deeper understanding of how communication protocols operate internally.

---

# Repository Structure

```text
BitBanging/
│
├── UART/
│   ├── README.md
│   ├── Arduino/
│   ├── STM32_HAL/
│   └── STM32_BareMetal/
│
├── I2C/
│   ├── README.md
│   ├── STM32_BitBang/
│   ├── BMP280 Driver/
│   └── LCD Interface/
│
├── Images/
│
└── README.md
```

---

# Repository Overview

## UART

Software implementation of UART communication using GPIO pins.

Implemented on

- Arduino Uno (ATmega328P)
- STM32 Nucleo-F446RE

📄 See `UART/README.md`

---

## I²C

Software implementation of the I²C protocol using GPIO bit banging.

Implemented on

- STM32 Nucleo-F446RE

Applications

- BMP280 Temperature Sensor Driver
- I²C LCD Interface

📄 See `I2C/README.md`

---

# Hardware Used

- STM32 Nucleo-F446RE
- Arduino Uno
- BMP280 Sensor
- I²C LCD (PCF8574)
- Logic Analyzer

---

# Development Approach

Every protocol is implemented from scratch to understand the complete communication sequence.

The implementation emphasizes

- Embedded C
- GPIO Manipulation
- Software Timing
- Register-Level Programming
---

# Validation

Each implementation is verified using a Logic Analyzer.

Validation includes

- Frame Timing
- Protocol Timing
- ACK / NACK Detection
- Register Transactions
- Device Communication
- Sensor Data Verification

---

# Learning Outcomes

This repository demonstrates practical experience in

- Embedded C
- STM32 Firmware Development
- HAL Driver Development
- Bare Metal Programming
- GPIO Programming
- UART Protocol
- I²C Protocol
- Sensor Driver Development
- LCD Driver Development
- Logic Analyzer Debugging
- Embedded Firmware Validation

---

# Future Work

The repository will continue to expand with additional software protocol implementations.

Planned additions include

- SPI Bit Banging
- SPI Sensor Drivers
- Driver Abstraction Layer


---

GitHub: 
https://github.com/matheshembed