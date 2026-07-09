#include <SPI.h>

volatile uint8_t txData = 100;
volatile uint8_t rxData = 0;

ISR(SPI_STC_vect)
{
    rxData = SPDR;      // Receive byte from STM32

    SPDR = txData;      // Send current byte back

    txData++;           // Prepare next byte
}

void setup()
{
    Serial.begin(115200);

    pinMode(MISO, OUTPUT);
    pinMode(SS, INPUT_PULLUP);

    SPCR |= _BV(SPE);      // SPI Slave Enable
    SPI.attachInterrupt();

    SPDR = txData;
}

void loop()
{
    static uint8_t last = 255;

    if(last != rxData)
    {
        Serial.print("Received : ");
        Serial.println(rxData);

        last = rxData;
    }
}