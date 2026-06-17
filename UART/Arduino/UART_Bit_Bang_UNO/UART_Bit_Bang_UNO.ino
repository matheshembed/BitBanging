
volatile long wait = 1;

char inport(void);
void outport(char bit);
void init_port(void);
void UART_sender(unsigned char data);
void delay1(unsigned long n);

void setup()
{
    init_port();

    while(1)
    {
        unsigned char input = inport();

        if(input == 0x01)
        {
            UART_sender(0xFF);
        }

        if(input == 0x02)
        {
            UART_sender(0x81);
        }
    }
}

void loop()
{
}

/*--------------------------------------------------*/
/* UART TRANSMITTER                                 */
/*--------------------------------------------------*/

void UART_sender(unsigned char data)
{
    unsigned char i;

    /* UART Idle = HIGH */
    outport(1);

    /* Start Bit = LOW */
    outport(0);
    delay1(wait);

    /* 8 Data Bits (LSB First) */
    for(i = 0; i < 8; i++)
    {
        outport((data >> i) & 0x01);
        delay1(wait);
    }

    /* Stop Bit = HIGH */
    outport(1);
    delay1(wait);
}

/*--------------------------------------------------*/
/* GPIO INITIALIZATION                              */
/*--------------------------------------------------*/

void init_port(void)
{
    volatile unsigned char *ddrb = (volatile unsigned char *)0x24;

    /* PB0 output (Arduino D8) */
    *ddrb |= 0x01;

    /* UART idle state HIGH */
    outport(1);
}

/*--------------------------------------------------*/
/* PB0 OUTPUT                                       */
/*--------------------------------------------------*/

void outport(char bit)
{
    volatile unsigned char *portb =
        (volatile unsigned char *)0x25;

    if(bit)
    {
        *portb |= 0x01;
    }
    else
    {
        *portb &= 0xFE;
    }
}

/*--------------------------------------------------*/
/* PORTD INPUT                                      */
/*--------------------------------------------------*/

char inport(void)
{
    volatile unsigned char *pind = (volatile unsigned char *)0x29;

    return *pind;
}

/*--------------------------------------------------*/
/* SOFTWARE DELAY                                   */
/*--------------------------------------------------*/

void delay1(unsigned long n)
{
    volatile unsigned long i;

    while(n--)
    {
        for(i = 0; i < 1000; i++)
        {
            ;
        }
    }
}
