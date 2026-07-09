/*
 * stm32f446xx_gpio_driver.c
 *
 *  Created on: 24-Mar-2026
 *      Author: mathe
 */

#include "stm32f446xx_gpio_driver.h"

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE)
	    {
	        if(pGPIOx == GPIOA)
	        {
	            GPIOA_PCLK_EN();
	        }
	        else if(pGPIOx == GPIOB)
	        {
	            GPIOB_PCLK_EN();
	        }
	        else if(pGPIOx == GPIOC)
	        {
	            GPIOC_PCLK_EN();
	        }
	        else if(pGPIOx == GPIOD)
	        {
	            GPIOD_PCLK_EN();
	        }
	        else if(pGPIOx == GPIOE)
	        {
	            GPIOE_PCLK_EN();
	        }
	        else if(pGPIOx == GPIOF)
	        {
	            GPIOF_PCLK_EN();
	        }
	        else if(pGPIOx == GPIOG)
	        {
	            GPIOG_PCLK_EN();
	        }
	        else if(pGPIOx == GPIOH)
	        {
	            GPIOH_PCLK_EN();
	        }
	    }
	    else
	    {
	        if(pGPIOx == GPIOA)
	        {
	            GPIOA_PCLK_DI();
	        }
	        else if(pGPIOx == GPIOB)
	        {
	            GPIOB_PCLK_DI();
	        }
	        else if(pGPIOx == GPIOC)
	        {
	            GPIOC_PCLK_DI();
	        }
	        else if(pGPIOx == GPIOD)
	        {
	            GPIOD_PCLK_DI();
	        }
	        else if(pGPIOx == GPIOE)
	        {
	            GPIOE_PCLK_DI();
	        }
	        else if(pGPIOx == GPIOF)
	        {
	            GPIOF_PCLK_DI();
	        }
	        else if(pGPIOx == GPIOG)
	        {
	            GPIOG_PCLK_DI();
	        }
	        else if(pGPIOx == GPIOH)
	        {
	            GPIOH_PCLK_DI();
	        }
	    }
}


void GPIO_Init(GPIO_Handle_t *pGPIOHandle){

	uint32_t temp=0;

	//1.Configure the mode of the GPIO Pin

	if(pGPIOHandle ->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
		// The above condition is for Modes other that  Interrupts because that gonna require some other configuration
		// The non interrupt mode
		temp = (pGPIOHandle ->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle ->GPIO_PinConfig.GPIO_PinNumber) );
																// Multiplying 2 with the pin number because of the 2 bit fields in the moder register
		// For Example if the pin number is 1
		// it will be multiplied by 2 and results in = 2
		// So the pin Mode value will be left shifted 2 times. like that...

		// Storing the temp value in the actual register
		//Before storing the value make sure the register is cleared
		pGPIOHandle->pGPIOx->MODER &= (~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Clearing
		pGPIOHandle->pGPIOx ->MODER |= temp;// Setting
	}
	else{
		// Refer 01_Gpio_Pin_Interrupt_Configuration Concept
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			//1. Configure  the falling edge selection register(FTSR).
			EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//Clear the corresponding RTSR bit .. Because we just want the falling edge trigger.
			EXTI->RTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			//1. Configure the RTSR
			EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//Clear the corresponding FTSR bit
			EXTI->FTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			//1. Configure both FTSR and RTSR
			EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

			EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		//2. Configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4 ;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] = portcode << ( temp2 * 4);

		//3. Enable the EXTI interrupt delivery using IMR
		EXTI->IMR |= 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
	}

	temp = 0;

	//2. Configure the speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= (~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinMode)); // Clearing
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	temp= 0;

	//3. Configure the pupd settings
	temp= (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= (~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Clearing
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	temp=0;

	//4. Congigure the output type
	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (1 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER &= (~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Clearing
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp =0;

	//5. Configure the Alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){
		// CONFIGURE THE ALF FUNCTION REGISTER

		// The AFR is divided into lower and higher register
		// Necessary Mathematics has to be done to deliver the values to the appropriate register and bit position

		uint8_t temp1,temp2;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8 ;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8 ;
		// The Division and Doing the Modulo operation is to select the appropriate ALTR function LOW and HIGH register respectively
		// It is a 4 bit field separated register so, that is the reason to multiply it by 4.
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4* temp2)); // Clearing

		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2 ));

	}


}// Function ENds

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}
	else if(pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}
	else if(pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}
	else if(pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}
	else if(pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}
	else if(pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();
	}
	else if(pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();
	}
	else if(pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	}

}// FUNCTION ENDS HERE

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){

	uint8_t value ;
	// Fetching the value from the Input data register using AND gate and bit right shifting
	value = (uint8_t) ((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;
}//FUNCTION ENDS HERE

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx ){
	uint16_t value ;
	value = (uint16_t) pGPIOx->IDR;
	return value;
}//FUNCTION ENDS HERE


void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value){

	if(Value == GPIO_PIN_SET){
		//write 1 to the output data register at the bit field corresponding to the pin number
		pGPIOx->ODR |= (1 << PinNumber);

	}else{
		//write 0
		pGPIOx->ODR &= ~(1 << PinNumber);
	}

}//FUNCTION ENDS HERE

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value){

	pGPIOx->ODR = Value;

}//FUNCTION ENDS HERE

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){

	pGPIOx->ODR ^= (1 << PinNumber);
	//Bit wise xor operation
}// FUNCTION ENDS HERE


/*
 * *******************************************GPIO IRQ Handling functions********************************************/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	/*To find the appropriate register for the respective IRQNumber
	 *The if and else if blocks are being created
	 *Refer 01_Gpio_Pin_Interrupt_Configuration concept
	*/
	 if(EnorDi == ENABLE)
	    {
	        if(IRQNumber <= 31)
	        {
	            /* Program ISER0 register */
	            *NVIC_ISER0 |= (1 << IRQNumber);
	        }
	        else if(IRQNumber > 31 && IRQNumber < 64)
	        {
	            /* Program ISER1 register (32 to 63) */
	            *NVIC_ISER1 |= (1 << (IRQNumber % 32));
	        }
	        else if(IRQNumber >= 64 && IRQNumber < 96)
	        {
	            /* Program ISER2 register (64 to 95) */
	            *NVIC_ISER2 |= (1 << (IRQNumber % 64));
	        }
	    }
	 else
	     {
	         if(IRQNumber <= 31)
	         {
	             /* Program ICER0 register */
	             *NVIC_ICER0 |= (1 << IRQNumber);
	         }
	         else if(IRQNumber > 31 && IRQNumber < 64)
	         {
	             /* Program ICER1 register (32 to 63) */
	             *NVIC_ICER1 |= (1 << (IRQNumber % 32));
	         }
	         else if(IRQNumber >= 64 && IRQNumber < 96)
	         {
	             /* Program ICER2 register (64 to 95) */
	             *NVIC_ICER2 |= (1 << (IRQNumber % 64));
	         }
	     }
}

void GPIO_IRQPriorityConfig(uint8_t IRQnumber, uint32_t IRQPriority)
{
	/*
	 * There are total of 60 Interrupt Priority registers and each register is of 32 bits
	 * Refer Section 4.2.7 On the ARM coretx guide
	 *
	 */

	//1. First lets find out the ipr register
	uint8_t iprx = IRQnumber / 4;
	uint8_t iprx_section = IRQnumber % 4;

    uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED); // only the highest 4 bits are implemented on each section that is why in total of 8 bits we are subtracting 4 bits
    *(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);

}

void GPIO_IRQHandling(uint8_t PinNumber)
{
    /* Clear the PR register corresponding to pin number */
    if(EXTI->PR & (1 << PinNumber))
    {
        /* Clear pin */
        EXTI->PR |= (1 << PinNumber);
    }
}


