//Tx data from the UNO TO Stm
void setup()
{
    Serial.begin(9600);
}

void loop()
{
    for(char c = '0'; c <= '9'; c++)
    {
        Serial.write(c);
        delay(500);
    }
}