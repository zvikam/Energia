/*
  Test case to verify SPI APIs

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the messages displayed on the Serial Monitor.
*/

#include "SPI.h"

void setup()
{
    int    value;
    int    index;

    Serial.println("SPI Module Example!!\r\n");

    SPI.begin();

    SPI.setLoopBackMode(1);

    for (index = 0; index < 0xFF; index++)
    {
        value = 0;

        value = SPI.transfer(index);
        if (value != index)
        {
            Serial.print("SPI.transfer() Failed for value: ");
            Serial.println((long)index);
            Serial.println("SPI Module Example Failed");
            break;
        }
    }

    if (0xFF == index)
    {
        Serial.print("SPI.transfer() with values from 0 - 0xFF ");
        Serial.println("Successful");
        Serial.print("The values written and when read back are same in ");
        Serial.println("Loopback mode");
        Serial.println("\r\nSPI Module Example Completed Successfully");
    }

    Serial.println("\r\nEnd of SPI Module Example");

    SPI.end();
}

void loop()
{

}
