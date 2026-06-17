#include "uart.h"


/* GPIO Clock Enable */
#define GPIOBEN    (1U << 1)

/* Function Prototypes */
void GPIOB_Init(void);
void DWT_Init(void);

void BitDelay(void);
void BitDelay_1_5(void);

void UART_SendByte(uint8_t data);
void UART_SendString(char *str);
uint8_t UART_ReceiveByte(void);
void Clock_Init_84MHz(void );

volatile uint8_t rx;

int main(void)
{
	Clock_Init_84MHz(); //Make sure your Clock runs at certain speed to maintain the baud rate
	DWT_Init();
    GPIOB_Init();



    while(1)
    {
        rx = UART_ReceiveByte();

        /* Echo back received character - 1 */
        UART_SendByte(rx - 1);
    }
}

void GPIOB_Init(void)
{
    /* Enable GPIOB clock */
    RCC->AHB1ENR |= GPIOBEN;

    /* PB13 = INPUT */

    GPIOB->MODER &= ~(3U << 26);

    /* PB13 Pull-up */

    GPIOB->PUPDR &= ~(3U << 26);
    GPIOB->PUPDR |=  (1U << 26);

    /* PB14 = OUTPUT */

    GPIOB->MODER &= ~(3U << 28);
    GPIOB->MODER |=  (1U << 28);

    /* UART idle state = HIGH */

    GPIOB->BSRR = (1U << 14);
}

void DWT_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    DWT->CYCCNT = 0;

    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void BitDelay(void)
{
    uint32_t start = DWT->CYCCNT;

    while((DWT->CYCCNT - start) < 8736)
    {
    }
}

void UART_StartBit(void)
{
    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
    GPIOB->BSRR &= ~(1U << 14); // Reset
    BitDelay();

    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
    GPIOB->ODR |= (1U << 14);
}

void UART_SendByte(uint8_t data)
{
    /* Start bit = LOW */

    GPIOB->BSRR = (1U << (14 + 16));

    BitDelay();

    /* 8 Data Bits */

    for(uint8_t i = 0; i < 8; i++)
    {
        if(data & (1U << i))
        {
            GPIOB->BSRR = (1U << 14);
        }
        else
        {
            GPIOB->BSRR = (1U << (14 + 16));
        }

        BitDelay();
    }

    /* Stop Bit = HIGH */

    GPIOB->BSRR = (1U << 14);

    BitDelay();
}

void UART_SendString(char *str)
{
    while(*str)
    {
        UART_SendByte(*str++);
    }
}

uint8_t UART_ReceiveByte(void)
{
    uint8_t data = 0;

    /* Wait for Start Bit */

    while(GPIOB->IDR & (1U << 13));

    /* Move to center of first data bit */

    BitDelay_1_5();

    /* Read 8 data bits */

    for(uint8_t i = 0; i < 8; i++)
    {
        if(GPIOB->IDR & (1U << 13))
        {
            data |= (1U << i);
        }

        BitDelay();
    }

    /* Optional Stop Bit Check */

    if(!(GPIOB->IDR & (1U << 13)))
    {
        /* Framing Error */
    }

    return data;
}

void BitDelay_1_5(void)
{
    uint32_t start = DWT->CYCCNT;

    while((DWT->CYCCNT - start) < 13104)
    {
    }
}

void Clock_Init_84MHz(void)
{
    /* Enable HSI */
    RCC->CR |= RCC_CR_HSION;

    while(!(RCC->CR & RCC_CR_HSIRDY));

    /* PLL Configuration */

    RCC->PLLCFGR = 0;

    RCC->PLLCFGR |= (16U << RCC_PLLCFGR_PLLM_Pos);   // PLLM = 16
    RCC->PLLCFGR |= (336U << RCC_PLLCFGR_PLLN_Pos);  // PLLN = 336

    /* PLLP = 4
     * 00 -> /2
     * 01 -> /4
     */

    RCC->PLLCFGR |= (1U << RCC_PLLCFGR_PLLP_Pos);

    /* HSI as PLL source */

    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC;

    /* Enable PLL */

    RCC->CR |= RCC_CR_PLLON;

    while(!(RCC->CR & RCC_CR_PLLRDY));

    /* Flash wait states */

    FLASH->ACR |= FLASH_ACR_LATENCY_2WS;

    /* Switch SYSCLK to PLL */

    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}
