/*
 * stm32f446xx.h
 *
 *  Created on: 07-Jul-2026
 *      Author: mathe
 */

/* This is the mcu Specific Header file */

#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_

#include <stdio.h>
#include <stdint.h>

#define __vo volatile

/******************************************************START: Processor Specific Details**********************************************/
/*
 * ARM CORTEX Mx processor NVIC ISERx register address
 */

#define NVIC_ISER0      ( (__vo uint32_t*)0xE000E100 )
#define NVIC_ISER1      ( (__vo uint32_t*)0xE000E104 )
#define NVIC_ISER2      ( (__vo uint32_t*)0xE000E108 )
#define NVIC_ISER3      ( (__vo uint32_t*)0xE000E10C )
#define NVIC_ISER4      ( (__vo uint32_t*)0xE000E110 )
#define NVIC_ISER5      ( (__vo uint32_t*)0xE000E114 )
#define NVIC_ISER6      ( (__vo uint32_t*)0xE000E118 )
#define NVIC_ISER7      ( (__vo uint32_t*)0xE000E11C )


/*
 * ARM Cortex Mx Processor NVIC ICERx Register Addresses
 */
#define NVIC_ICER0      ( (__vo uint32_t*)0XE000E180 )
#define NVIC_ICER1      ( (__vo uint32_t*)0XE000E184 )
#define NVIC_ICER2      ( (__vo uint32_t*)0XE000E188 )
#define NVIC_ICER3      ( (__vo uint32_t*)0XE000E18C )
#define NVIC_ICER4      ( (__vo uint32_t*)0XE000E190 )
#define NVIC_ICER5      ( (__vo uint32_t*)0XE000E194 )
#define NVIC_ICER6      ( (__vo uint32_t*)0XE000E198 )
#define NVIC_ICER7      ( (__vo uint32_t*)0XE000E19C )


/*
 * ARM Cortex Mx Processor Priority Register Address Calculation
 */
#define NVIC_PR_BASE_ADDR   ( (__vo uint32_t*)0XE000E400 )


/*
 * ARM Cortex Mx Processor number of priority bits implemented in Priority Register
 */
#define NO_PR_BITS_IMPLEMENTED  4

/*************************************************************************************************************************************/




/*
 * Some Generic Macros
 */
/*************************************************************************************************************************************/
#define ENABLE				1
#define DISABLE				0
#define SET 				ENABLE
#define RESET				DISABLE
#define GPIO_PIN_SET		SET
#define GPIO_PIN_RESET		RESET





/*****************************************************************************************************************************************/
/*=================================================================================================================================*/

/* BASE ADDRESSES OF FLASH AND SRAM MEMORIES */

/*Refer 00_Flash_&_Ram Q&A*/

#define FLASH_BASE_ADDR		0x08000000U		/*BASE ADDRESS OF THE FLASH*/
#define SRAM1_BASE_ADDR		0x20000000U		/*BASE ADDRESS OF THE SRAM1*/
#define SRAM2_BASE_ADDR		0x2001C000U		/*BASE ADDRESS OF THE SRAM2*/
#define ROM_BASE_ADDR		0x1FFF0000U		/*BASE ADDRESS OF THE ROM*/
#define SRAM 				SRAM1_BASE_ADDR

/* BASE ADDRESSES OF AHBx and APBx PERIPHERALS */

#define PERIPH_BASE_ADDR		0x40000000U
#define APB1_PERI_BASE_ADDR		PERIPH_BASE_ADDR
#define APB2_PERI_BASE_ADDR		0x40010000U
#define AHB1_PERI_BASE_ADDR		0x40020000U
#define AHB2_PERI_BASE_ADDR		0x50000000U
#define AHB3_PERI_BASE_ADDR		0x60000000U

/*PERIPHERAL BASE ADDRESS CONNECTED TO THE AHB1 BUS */

#define GPIOA_BASE_ADDR 		(AHB1_PERI_BASE_ADDR + 0x0000)
#define GPIOB_BASE_ADDR 		(AHB1_PERI_BASE_ADDR + 0x0400)
#define GPIOC_BASE_ADDR 		(AHB1_PERI_BASE_ADDR + 0x0800)
#define GPIOD_BASE_ADDR 		(AHB1_PERI_BASE_ADDR + 0x0C00)
#define GPIOE_BASE_ADDR 		(AHB1_PERI_BASE_ADDR + 0x1000)
#define GPIOF_BASE_ADDR 		(AHB1_PERI_BASE_ADDR + 0x1400)
#define GPIOG_BASE_ADDR 		(AHB1_PERI_BASE_ADDR + 0x1800)
#define GPIOH_BASE_ADDR 		(AHB1_PERI_BASE_ADDR + 0x1C00)
#define RCC_BASE_ADDR			(AHB1_PERI_BASE_ADDR + 0x3800)



/*PERIPHERAL BASE ADDRESS CONNECTED TO THE APB1 BUS */

#define	I2C1_BASE_ADDR			(APB1_PERI_BASE_ADDR + 0x5400)
#define	I2C2_BASE_ADDR			(APB1_PERI_BASE_ADDR + 0x5800)
#define I2C3_BASE_ADDR			(APB1_PERI_BASE_ADDR + 0x5C00)


#define	USART2_BASE_ADDR        (APB1_PERI_BASE_ADDR + 0x4400)
#define USART3_BASE_ADDR        (APB1_PERI_BASE_ADDR + 0x4800)

#define UART4_BASE_ADDR         (APB1_PERI_BASE_ADDR + 0x4C00)
#define UART5_BASE_ADDR         (APB1_PERI_BASE_ADDR + 0x5000)

#define SPI2_BASE_ADDR		    (APB1_PERI_BASE_ADDR + 0x3800)
#define SPI3_BASE_ADDR		    (APB1_PERI_BASE_ADDR + 0xC800)


/* PERIPHERAL BASE ADDRESS CONNECETD TO APB2 BUS*/
#define SPI1_BASE_ADDR			(APB2_PERI_BASE_ADDR + 0x3000)
#define SPI4_BASE_ADDR			(APB2_PERI_BASE_ADDR + 0x3400)

#define USART1_BASE_ADDR     	(APB2_PERI_BASE_ADDR + 0x1000)
#define USART6_BASE_ADDR     	(APB2_PERI_BASE_ADDR + 0x1400)

#define SYSCFG_BASE_ADDR     	(APB2_PERI_BASE_ADDR + 0x3800)

#define EXTI_BASE_ADDR      	(APB2_PERI_BASE_ADDR + 0x3C00)


/*
 * *********************************************************************************************
 *			Peripheral register definition structures
 **********************************************************************************************
 *  		Peripheral register definition structure for GPIO
 */

typedef struct
{
    __vo uint32_t MODER;        /* GPIO port mode register,                         Address offset: 0x00    */
    __vo uint32_t OTYPER;       /* GPIO port output type register,                  Address offset: 0x04    */
    __vo uint32_t OSPEEDR;      /* GPIO port output speed register,                 Address offset: 0x08    */
    __vo uint32_t PUPDR;        /* GPIO port pull-up/down register,                 Address offset: 0x0C    */
    __vo uint32_t IDR;          /* GPIO port input data register,                   Address offset: 0x10    */
    __vo uint32_t ODR;          /* GPIO port output data register,                  Address offset: 0x14    */
    __vo uint32_t BSRR;         /* GPIO port bit set/reset register,                Address offset: 0x18    */
    __vo uint32_t LCKR;         /* GPIO port configuration lock register,           Address offset: 0x1C    */
    __vo uint32_t AFR[2];       /* AFR[0]: GPIO alternate function low register,	Address offset: 0x20
                                   AFR[1]: GPIO alternate function high register,   Address offset: 0x24 	*/
}GPIO_RegDef_t;


/* Peripheral definition of rcc registers */

typedef struct
{
    __vo uint32_t CR;           /* RCC clock control register,                                  Address offset: 0x00    */
    __vo uint32_t PLLCFGR;      /* RCC PLL configuration register,                              Address offset: 0x04    */
    __vo uint32_t CFGR;         /* RCC clock configuration register,                            Address offset: 0x08    */
    __vo uint32_t CIR;          /* RCC clock interrupt register,                                Address offset: 0x0C    */
    __vo uint32_t AHB1RSTR;     /* RCC AHB1 peripheral reset register,                          Address offset: 0x10    */
    __vo uint32_t AHB2RSTR;     /* RCC AHB2 peripheral reset register,                          Address offset: 0x14    */
    __vo uint32_t AHB3RSTR;     /* RCC AHB3 peripheral reset register,                          Address offset: 0x18    */
    uint32_t      RESERVED0;    /* RCC reserved register,                                       Address offset: 0x1C    */
    __vo uint32_t APB1RSTR;     /* RCC APB1 peripheral reset register,                          Address offset: 0x20 	*/
    __vo uint32_t APB2RSTR;     /* RCC APB2 peripheral reset register,                          Address offset: 0x24    */
    uint32_t      RESERVED1[2]; /* RCC reserved register,                                       Address offset: 0x28-2C */
    __vo uint32_t AHB1ENR;      /* RCC AHB1 peripheral clock enable register,                   Address offset: 0x30    */
    __vo uint32_t AHB2ENR;      /* RCC AHB2 peripheral clock enable register,                   Address offset: 0x34    */
    __vo uint32_t AHB3ENR;      /* RCC AHB3 peripheral clock enable register,                   Address offset: 0x38    */
    uint32_t      RESERVED2;    /* RCC reserved register,                                       Address offset: 0x3C    */
    __vo uint32_t APB1ENR;      /* RCC APB1 peripheral clock enable register,                   Address offset: 0x40    */
    __vo uint32_t APB2ENR;      /* RCC APB2 peripheral clock enable register,                   Address offset: 0x44    */
    uint32_t      RESERVED3[2];	/* RCC reserved register,                                       Address offset: 0x48-4C */
    __vo uint32_t AHB1LPENR;    /* RCC AHB1 peripheral clock enable in low power mode register,	Address offset: 0x50    */
    __vo uint32_t AHB2LPENR;	/* RCC AHB2 peripheral clock enable in low power mode register,	Address offset: 0x54 	*/
    __vo uint32_t AHB3LPENR;	/* RCC AHB3 peripheral clock enable in low power mode register,	Address offset: 0x58 	*/
    uint32_t      RESERVED4;    /* RCC reserved register,                                       Address offset: 0x5C    */
    __vo uint32_t APB1LPENR;    /* RCC APB1 peripheral clock enable in low power mode register,	Address offset: 0x60    */
    __vo uint32_t APB2LPENR;    /* RCC APB2 peripheral clock enable in low power mode register,	Address offset: 0x64    */
    uint32_t      RESERVED5[2]; /* RCC reserved register,                                       Address offset: 0x68-6C */
    __vo uint32_t BDCR;         /* RCC back up domain control register,                         Address offset: 0x70    */
    __vo uint32_t CSR;          /* RCC clock control & status register,                         Address offset: 0x74    */
    uint32_t      RESERVED6[2]; /* RCC reserved register,                                       Address offset: 0x78-7C */
    __vo uint32_t SSCGR;        /* RCC spread spectrum clock generation register,               Address offset: 0x80    */
    __vo uint32_t PLLI2SCFGR;   /* RCC PLLI2S configuration register,                           Address offset: 0x84    */
    __vo uint32_t PLLSAICFGR;   /* RCC PLL configuration register,                              Address offset: 0x88    */
    __vo uint32_t DCKCFGR;      /* RCC dedicated clock configuration register,                  Address offset: 0x8C    */
    __vo uint32_t CKGATENR;     /* RCC clock gated enable register,                             Address offset: 0x90    */
    __vo uint32_t DCKCFGR2;     /* RCC dedicated clock configuration register 2,                Address offset: 0x94    */
}RCC_RegDef_t;


/*
 * Peripheral Register Definition Structure for EXTI
 */
typedef struct
{
	__vo uint32_t IMR;				//			Address offset: 0x00
	__vo uint32_t EMR;				//			Address offset: 0x04
	__vo uint32_t RTSR;				//			Address offset: 0x08
	__vo uint32_t FTSR;				//			Address offset: 0x0C
	__vo uint32_t SWIER;			//			Address offset: 0x10
	__vo uint32_t PR;				//			Address offset: 0x14
}EXTI_RegDef_t;

/*
 * Peripheral Register Definition Structure for SYSCFG
 */
typedef struct
{
	__vo uint32_t MEMRMP;			//			Address offset: 0x00
	__vo uint32_t PMC;				//			Address offset: 0x04
	__vo uint32_t EXTICR[4];		//			Address offset: 0x08
	__vo uint32_t RESERVED1[2];		//			Address offset: 0x0C
	__vo uint32_t CMPCR;			//			Address offset: 0x10
	__vo uint32_t RESERVED2[2];		//			Address offset: 0x0C
	__vo uint32_t CFGR;				//			Address offset: 0x14
}SYSCFG_RegDef_t;

/*
 * Peripheral register definition structure for SPI
 */
typedef struct
{
    __vo uint32_t CR1;      /* SPI control register 1,          Address offset: 0x00 */
    __vo uint32_t CR2;      /* SPI control register 2,          Address offset: 0x04 */
    __vo uint32_t SR;       /* SPI status register,             Address offset: 0x08 */
    __vo uint32_t DR;       /* SPI data register,               Address offset: 0x0C */
    __vo uint32_t CRCPR;    /* SPI CRC polynomial register,     Address offset: 0x10 */
    __vo uint32_t RXCRCR;   /* SPI RX CRC register,             Address offset: 0x14 */
    __vo uint32_t TXCRCR;   /* SPI TX CRC register,             Address offset: 0x18 */
    __vo uint32_t I2SCFGR;  /* SPI_I2S configuration register,  Address offset: 0x1C */
    __vo uint32_t I2SPR;    /* SPI_I2S prescaler register,      Address offset: 0x20 */
}SPI_RegDef_t;



/*
 * Peripheral definition (peripheral base address typecasted to xxx_RegDef_t)
 */

/* GPIO_RegDef_t *pGPIOA = GPIOA(base address of gpioa);*/


#define GPIOA					((GPIO_RegDef_t *)GPIOA_BASE_ADDR)
#define GPIOB					((GPIO_RegDef_t *)GPIOB_BASE_ADDR)
#define GPIOC					((GPIO_RegDef_t *)GPIOC_BASE_ADDR)
#define GPIOD					((GPIO_RegDef_t *)GPIOD_BASE_ADDR)
#define GPIOE					((GPIO_RegDef_t *)GPIOE_BASE_ADDR)
#define GPIOF					((GPIO_RegDef_t *)GPIOF_BASE_ADDR)
#define GPIOG					((GPIO_RegDef_t *)GPIOG_BASE_ADDR)
#define GPIOH					((GPIO_RegDef_t *)GPIOH_BASE_ADDR)

#define RCC            			((RCC_RegDef_t*) RCC_BASE_ADDR)
#define EXTI            		((EXTI_RegDef_t*) EXTI_BASE_ADDR)
#define SYSCFG          		((SYSCFG_RegDef_t*)SYSCFG_BASE_ADDR)

#define SPI1            		((SPI_RegDef_t*) SPI1_BASE_ADDR)
#define SPI2            		((SPI_RegDef_t*) SPI2_BASE_ADDR)
#define SPI3            		((SPI_RegDef_t*) SPI3_BASE_ADDR)
#define SPI4            		((SPI_RegDef_t*) SPI4_BASE_ADDR)

/*Clock Enable Macros for GPIOx Peripherals */

/* Go the address pointed by rcc and access the member AHB1ENR
 (*pointer).member
 RCC->AHB1ENR
 (*RCC).AHB1ENR  -- The compiler will reading this as *(RCC.AHB1ENR)

 because the member-access operator (.) binds tighter than the dereference operator (*). That means you’re attempting to treat the value of RCC.AHB1ENR as an address and dereference it—almost certainly not what you want.
 */

#define GPIOA_PCLK_EN()		(RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()		(RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR |= (1<<4))
#define GPIOF_PCLK_EN()		(RCC->AHB1ENR |= (1<<5))
#define GPIOG_PCLK_EN()		(RCC->AHB1ENR |= (1<<6))
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR |= (1<<7))

/*Clock Enable Macros for I2Cx Peripherals */
#define I2C1_PCLK_EN()		(RCC->APB1ENR |= (1<<21))
#define I2C2_PCLK_EN()		(RCC->APB1ENR |= (1<<22))
#define I2C3_PCLK_EN()		(RCC->APB1ENR |= (1<<23))

/*Clock Enable Macros for SPIx Peripherals*/
/* PCLK -> PERIPHERAL CLOCK */
#define SPI1_PCLK_EN()		(RCC->APB2ENR |= (1<<12))
#define SPI4_PCLK_EN()		(RCC->APB2ENR |= (1<<13))
#define SPI2_PCLK_EN()		(RCC->APB1ENR |= (1<<14))
#define SPI3_PCLK_EN()		(RCC->APB1ENR |= (1<<15))

/*Clock Enable Macros for USARTc Peripherals */
#define USART2_PCLK_EN()	(RCC->APB1ENR |= (1<<17))
#define USART3_PCLK_EN()	(RCC->APB1ENR |= (1<<18))
#define UART4_PCLK_EN()		(RCC->APB1ENR |= (1<<19))
#define UART5_PCLK_EN()		(RCC->APB1ENR |= (1<<20))
#define USART1_PCLK_EN()	(RCC->APB2ENR |= (1<<4))
#define USART6_PCLK_EN()	(RCC->APB2ENR |= (1<<5))

/*Clock Enable Macros for SYSCFG peripheral*/
#define SYSCFG_PCLK_EN()    (RCC->APB2ENR |= (1<<14)) /* SYSCFG peripheral clock enabled */

/*Clock Disable Macros for GPIOx Peripherals*/
#define GPIOA_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<4))
#define GPIOF_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<5))
#define GPIOG_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<6))
#define GPIOH_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<7))

/* Clock Disable Macros for I2Cx peripherals*/
#define I2C1_PCLK_DI()		(RCC->APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI()		(RCC->APB1ENR &= ~(1<<22))
#define I2C3_PCLK_DI()		(RCC->APB1ENR &= ~(1<<23))

/*
 * Clock Disable Macros for SPIx peripherals
 */
#define SPI1_PCLK_DI()      ( RCC->APB2ENR &= ~(1 << 12) ) /* SPI1 peripheral clock disabled */
#define SPI2_PCLK_DI()      ( RCC->APB1ENR &= ~(1 << 14) ) /* SPI2 peripheral clock disabled */
#define SPI3_PCLK_DI()      ( RCC->APB1ENR &= ~(1 << 15) ) /* SPI3 peripheral clock disabled */
#define SPI4_PCLK_DI()      ( RCC->APB2ENR &= ~(1 << 13) ) /* SPI4 peripheral clock disabled */

/*Clock Disable Macros for USARTx Peripherals*/
#define USART2_PCLK_DI()	(RCC->APB1ENR &= ~(1<<17))
#define USART3_PCLK_DI()	(RCC->APB1ENR &= ~(1<<18))
#define UART4_PCLK_DI()		(RCC->APB1ENR &= ~(1<<19))
#define UART5_PCLK_DI()		(RCC->APB1ENR &= ~(1<<20))
#define USART1_PCLK_DI()	(RCC->APB2ENR &= ~(1<<4))
#define USART6_PCLK_DI()	(RCC->APB2ENR &= ~(1<<5))

/*Clock Disable Macros for SYSCFG Peripheral*/
#define SYSCFG_PCLK_DI()    (RCC->APB2ENR &= ~(1<<14))

/* Macros to reset GPIOx Peripherals*/
// If the respective bit field has the value one ... then the peripheral is re setted till it is low .. so that is why we have to make it HIGH once and make it low.
// This is how we have to include two statements into a single macro .. use a do while loop
// Don't give the semicolon at the end because when we use this macro .. we give a semicolon so no need here
// Why specifically do while -> Runs safely inside if statements if we do not use do while .. then the first line only will be added inside the if block and why while(0)because we dont want to repeat and while(0) is falese ..
#define GPIOA_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 0 )); (RCC->AHB1RSTR &= ~(1 <<0 )); }while(0)
#define GPIOB_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 1 )); (RCC->AHB1RSTR &= ~(1 <<0 )); }while(0)
#define GPIOC_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 2 )); (RCC->AHB1RSTR &= ~(1 <<0 )); }while(0)
#define GPIOD_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 3 )); (RCC->AHB1RSTR &= ~(1 <<0 )); }while(0)
#define GPIOE_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 4 )); (RCC->AHB1RSTR &= ~(1 <<0 )); }while(0)
#define GPIOF_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 5 )); (RCC->AHB1RSTR &= ~(1 <<0 )); }while(0)
#define GPIOG_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 6 )); (RCC->AHB1RSTR &= ~(1 <<0 )); }while(0)
#define GPIOH_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 7 )); (RCC->AHB1RSTR &= ~(1 <<0 )); }while(0)

/*
 * Macros to reset SPIx peripherals
 */
#define SPI1_REG_RESET()    do{ (RCC->APB2RSTR |= (1 << 12)); (RCC->APB2RSTR &= ~(1 << 12)); }while(0)
#define SPI2_REG_RESET()    do{ (RCC->APB1RSTR |= (1 << 14)); (RCC->APB1RSTR &= ~(1 << 14)); }while(0)
#define SPI3_REG_RESET()    do{ (RCC->APB1RSTR |= (1 << 15)); (RCC->APB1RSTR &= ~(1 << 15)); }while(0)
#define SPI4_REG_RESET()    do{ (RCC->APB2RSTR |= (1 << 13)); (RCC->APB2RSTR &= ~(1 << 13)); }while(0)

/* This macro returns a code( between 0 to 7) for a given GPIO base address(x)
 */
//   "\" tells the macro is going to be continued in the next line.
#define GPIO_BASEADDR_TO_CODE(x)      ( (x == GPIOA)?0:\
										(x == GPIOB)?1:\
										(x == GPIOC)?2:\
										(x == GPIOD)?3:\
								        (x == GPIOE)?4:\
								        (x == GPIOF)?5:\
								        (x == GPIOG)?6:\
								        (x == GPIOH)?7:0)



/*
 * IRQ(Interrupt Request) Numbers of STM32F446x MCU
 * NOTE: Update these macros with valid values according to your MCU
 */
#define IRQ_NO_WWDG                 0   /* Window Watchdog interrupt                                            */
#define IRQ_NO_PVD                  1   /* PVD through EXTI line detection interrupt                            */
#define IRQ_NO_TAMP_STAMP           2   /* Tamper and Time stamp interrupts through EXTI line                   */
#define IRQ_NO_RTC_WKUP             3   /* RTC Wakeup interrupt through EXTI line                               */
#define IRQ_NO_FLASH                4   /* Flash global interrupt                                               */
#define IRQ_NO_RCC                  5   /* RCC global interrupt                                                 */
#define IRQ_NO_EXTI0                6   /* EXTI Line0 interrupt                                                 */
#define IRQ_NO_EXTI1                7   /* EXTI Line1 interrupt                                                 */
#define IRQ_NO_EXTI2                8   /* EXTI Line2 interrupt                                                 */
#define IRQ_NO_EXTI3                9   /* EXTI Line3 interrupt                                                 */
#define IRQ_NO_EXTI4                10  /* EXTI Line4 interrupt                                                 */
#define IRQ_NO_DMA1_STREAM0         11  /* DMA1 Stream0 interrupt                                               */
#define IRQ_NO_DMA1_STREAM1         12  /* DMA1 Stream1 interrupt                                               */
#define IRQ_NO_DMA1_STREAM2         13  /* DMA1 Stream2 interrupt                                               */
#define IRQ_NO_DMA1_STREAM3         14  /* DMA1 Stream3 interrupt                                               */
#define IRQ_NO_DMA1_STREAM4         15  /* DMA1 Stream4 interrupt                                               */
#define IRQ_NO_DMA1_STREAM5         16  /* DMA1 Stream5 interrupt                                               */
#define IRQ_NO_DMA1_STREAM6         17  /* DMA1 Stream6 interrupt                                               */
#define IRQ_NO_ADC                  18  /* ADC1, ADC2 and ADC3 global interrupts                                */
#define IRQ_NO_CAN1_TX              19  /* CAN1 TX interrupts                                                   */
#define IRQ_NO_CAN1_RX0             20  /* CAN1 RX0 interrupts                                                  */
#define IRQ_NO_CAN1_RX1             21  /* CAN1 RX1 interrupts                                                  */
#define IRQ_NO_CAN1_SCE             22  /* CAN1 SCE interrupts                                                  */
#define IRQ_NO_EXTI9_5              23  /* EXTI Line[9:5] interrupts                                            */
#define	IRQ_NO_TIM1_BRK_TIM9        24  /* TIM1 Break interrupt and TIM9 global interrupt                       */
#define	IRQ_NO_TIM1_UP_TIM10        25  /* TIM1 Update interrupt and TIM10 global interrupt                     */
#define IRQ_NO_TIM1_TRG_COM_TIM11   26  /* TIM1 Trigger and Commutation interrupts and TIM11 global interrupt   */
#define IRQ_NO_TIM1_CC              27  /* TIM1 Capture Compare interrupt                                       */
#define IRQ_NO_TIM2                 28  /* TIM2 global interrupt                                                */
#define IRQ_NO_TIM3                 29  /* TIM3 global interrupt                                                */
#define IRQ_NO_TIM4                 30  /* TIM4 global interrupt                                                */
#define IRQ_NO_I2C1_EV              31  /* I2C1 event interrupt                                                 */
#define IRQ_NO_I2C1_ER              32  /* I2C1 error interrupt                                                 */
#define IRQ_NO_I2C2_EV              33  /* I2C2 event interrupt                                                 */
#define IRQ_NO_I2C2_ER              34  /* I2C2 error interrupt                                                 */
#define IRQ_NO_SPI1                 35  /* SPI1 global interrupt                                                */
#define IRQ_NO_SPI2                 36  /* SPI2 global interrupt                                                */
#define IRQ_NO_USART1               37  /* USART1 global interrupt                                              */
#define IRQ_NO_USART2               38  /* USART2 global interrupt                                              */
#define IRQ_NO_USART3               39  /* USART3 global interrupt                                              */
#define IRQ_NO_EXTI15_10            40  /* EXTI Line[15:10] interrupts                                          */
#define IRQ_NO_RTC_ALARM            41  /* RTC Alarms (A and B) through EXTI line interrupts                    */
#define IRQ_NO_OTG_FS_WKUP          42  /* USB On-The-Go FS Wakeup through EXTI line interrupt                  */
#define IRQ_NO_TIM8_BRK_TIM12       43  /* TIM8 Break interrupt and TIM12 global interrupt                      */
#define IRQ_NO_TIM8_UP_TIM13        44  /* TIM8 Update and TIM13 global interrupt                               */
#define IRQ_NO_TIM8_TRG_COM_TIM14   45  /* TIM8 Trigger and Commutation interrupts and TIM14 global interrupt   */
#define IRQ_NO_TIM8_CC              46  /* TIM8 Capture Compare interrupt                                       */
#define IRQ_NO_DMA1_STREAM7         47  /* DMA1 Stream7 global interrupt                                        */
#define IRQ_NO_FMC                  48  /* FMC global interrupt                                                 */
#define IRQ_NO_SDIO                 49  /* SDIO global interrupt                                                */
#define IRQ_NO_TIM5                 50  /* TIM5 global interrupt                                                */
#define IRQ_NO_SPI3                 51  /* SPI3 global interrupt                                                */
#define IRQ_NO_UART4                52  /* UART4 global interrupt                                               */
#define IRQ_NO_UART5                53  /* UART5 global interrupt                                               */
#define IRQ_NO_TIM6_DAC             54  /* TIM6 global interrupt, DAC1 and DAC2 underrun error interrupts       */
#define IRQ_NO_TIM7                 55  /* TIM7 global interrupt                                                */
#define IRQ_NO_DMA2_STREAM0         56  /* DMA2 Stream0 global interrupt                                        */
#define IRQ_NO_DMA2_STREAM1         57  /* DMA2 Stream1 global interrupt                                        */
#define IRQ_NO_DMA2_STREAM2         58  /* DMA2 Stream2 global interrupt                                        */
#define IRQ_NO_DMA2_STREAM3         59  /* DMA2 Stream3 global interrupt                                        */
#define IRQ_NO_DMA2_STREAM4         60  /* DMA2 Stream4 global interrupt                                        */
#define IRQ_NO_CAN2_TX              63  /* CAN2 TX interrupts                                                   */
#define IRQ_NO_CAN2_RX0             64  /* CAN2 RX0 interrupts                                                  */
#define IRQ_NO_CAN2_RX1             65  /* CAN2 RX1 interrupts                                                  */
#define IRQ_NO_CAN2_SCE             66  /* CAN2 SCE interrupts                                                  */
#define IRQ_NO_CAN2_OTG             67  /* USB On The Go FS global interrupt                                    */
#define IRQ_NO_DMA2_STREAM5         68  /* DMA2 Stream5 global interrupt                                        */
#define IRQ_NO_DMA2_STREAM6         69  /* DMA2 Stream6 global interrupt                                        */
#define IRQ_NO_DMA2_STREAM7         70  /* DMA2 Stream7 global interrupt                                        */
#define IRQ_NO_USART6               71  /* USART6 global interrupt                                              */
#define IRQ_NO_I2C3_EV              72  /* I2C3 event interrupt                                                 */
#define IRQ_NO_I2C3_ER              73  /* I2C3 error interrupt                                                 */
#define IRQ_NO_OTG_HS_EP1_OUT       74  /* USB On The Go HS End Point 1 Out global interrupt                    */
#define IRQ_NO_OTG_HS_EP1_IN        75  /* USB On The Go HS End Point 1 In global interrupt                     */
#define IRQ_NO_OTG_HS_WKUP          76  /* USB On The Go HS Wakeup through EXTI interrupt                       */
#define IRQ_NO_OTG_HS               77  /* USB On The Go HS global interrupt                                    */
#define IRQ_NO_DCMI                 78  /* DCMI global interrupt                                                */
#define IRQ_NO_FPU                  81  /* FPU global interrupt                                                 */
#define IRQ_NO_SPI4                 84  /* SPI4 global interrupt                                                */
#define IRQ_NO_SAI1                 87  /* SAI1 global interrupt                                                */
#define IRQ_NO_SAI2                 91  /* SAI2 global interrupt                                                */
#define IRQ_NO_QUADSPI              92  /* QuadSPI global interrupt                                             */
#define IRQ_NO_HDMI_CEC             93  /* HDMI-CEC global interrupt                                            */
#define IRQ_NO_SPDIF_RX             94  /* SPDIF-Rx global interrupt                                            */
#define IRQ_NO_FMPI2C1_EV           95  /* FMPI2C1 event interrupt                                              */
#define IRQ_NO_FMPI2C1_ER           96  /* FMPI2C1 error interrupt                                              */

/*
 * Macros for all possible priority levels
 */
#define NVIC_IRQ_PRI0       0
#define NVIC_IRQ_PRI1       1
#define NVIC_IRQ_PRI2       2
#define NVIC_IRQ_PRI3       3
#define NVIC_IRQ_PRI4       4
#define NVIC_IRQ_PRI5       5
#define NVIC_IRQ_PRI6       6
#define NVIC_IRQ_PRI7       7
#define NVIC_IRQ_PRI8       8
#define NVIC_IRQ_PRI9       9
#define NVIC_IRQ_PRI10      10
#define NVIC_IRQ_PRI11      11
#define NVIC_IRQ_PRI12      12
#define NVIC_IRQ_PRI13      13
#define NVIC_IRQ_PRI14      14
#define NVIC_IRQ_PRI15      15

/*
 * Generic Macros
 */
#define ENABLE          1
#define DISABLE         0
#define SET             ENABLE
#define RESET           DISABLE
#define GPIO_PIN_SET    SET
#define GPIO_PIN_RESET  RESET
#define FLAG_SET        SET
#define FLAG_RESET      RESET

/******************************************************************************************
 *			Bit position definitions of SPI peripheral
 ******************************************************************************************/
/*
 * Bit position definitions SPI_CR1
 */
#define SPI_CR1_CPHA        0
#define SPI_CR1_CPOL        1
#define SPI_CR1_MSTR        2
#define SPI_CR1_BR          3
#define SPI_CR1_SPE         6
#define SPI_CR1_LSB_FIRST   7
#define SPI_CR1_SSI         8
#define SPI_CR1_SSM         9
#define SPI_CR1_RX_ONLY     10
#define SPI_CR1_DFF         11
#define SPI_CR1_CRC_NEXT    12
#define SPI_CR1_CRC_EN      13
#define SPI_CR1_BIDI_OE     14
#define SPI_CR1_BIDI_MODE   15

/*
 * Bit position definitions SPI_CR2
 */
#define SPI_CR2_RXDMAEN     0
#define SPI_CR2_TXDMAEN     1
#define SPI_CR2_SSOE        2
#define SPI_CR2_FRF         4
#define SPI_CR2_ERRIE       5
#define SPI_CR2_RXNEIE      6
#define SPI_CR2_TXEIE       7

/*
 * Bit position definitions SPI_SR
 */
#define SPI_SR_RXNE         0
#define SPI_SR_TXE          1
#define SPI_SR_CHSIDE       2
#define SPI_SR_UDR          3
#define SPI_SR_CRC_ERR      4
#define SPI_SR_MODF         5
#define SPI_SR_OVR          6
#define SPI_SR_BSY          7
#define SPI_SR_FRE          8



#include "stm32f446xx_gpio_driver.h"
/* ==============================================================================================================================*/

#endif /* INC_STM32F446XX_H_ */


