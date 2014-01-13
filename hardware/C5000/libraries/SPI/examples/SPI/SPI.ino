/*
 * SPI loopback demo
 * Writes data to SPI register and reads it back in loopback mode
 */

#include "SPI.h"

void setup()
{
    int    value;
    int    index;

    Serial.println("\r\nSPI Read/Write Demo");

    SPI.begin();

    /* Setting loopback mode, such that we get back the same data which we are
       writing to SPI */
    SPI.setLoopBackMode(1);

    for (index = 0; index < 0xFF; index++)
    {
        value = 0;
        
        /* Writes the value of 'index' to SPI write register, reads it
           back and returns the vaue read */
        value = SPI.transfer(index);
        if (value != index)
        {
            Serial.print("SPI.transfer() Failed for value: ");
            Serial.println(index);
            break;
        }
    }

    if (0xFF == index)
    {
        Serial.print("SPI.transfer() with values from 0 - 0xFF ");
        Serial.println("Successful");
        Serial.print("The values written and when read back are same in ");
        Serial.println("Loopback mode");
    }

    Serial.println("\r\nEnd of SPI Read/Write Demo");

    SPI.end();
}

void loop()
{
}
