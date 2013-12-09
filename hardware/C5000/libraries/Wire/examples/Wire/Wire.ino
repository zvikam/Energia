/*
  Wire/I2C Example

  This example will write a value into codec register, reads it back and
  compares them.

  Procedure to run the example:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the output on the Serial Monitor.
*/

void codecFunc(unsigned int regAddr, unsigned int value)
{
    unsigned int i2cRdBuf[2];
    unsigned int i2cWrBuf[2];
    unsigned int bytesAvail;
    int          status;

    i2cWrBuf[0] = regAddr;
    i2cWrBuf[1] = value;
    i2cRdBuf[0] = 0xFF;
    i2cRdBuf[1] = 0xFF;

    status = Wire.beginTransmission(0x18);
    if(status != 0)
    {
        Serial.print("Wire.beginTransmission() failed with status ");
        Serial.println((long)status);
    }
    else
    {
        status = Wire.write((unsigned int *)i2cWrBuf, 2);
        if(status != 2)
        {
            Serial.print("Wire.write() failed with number of bytes written ");
            Serial.println((long)status);
        }
        else
        {
            status = Wire.endTransmission();
            if(status != 0)
            {
                Serial.print("Wire.endTransmission() failed with status ");
                Serial.println((long)status);
            }
            else
            {
                Serial.print("Value written is ");
                Serial.println((long)value);

        		status = Wire.requestFrom(0x18, 1, (unsigned int *)&regAddr, 1);
                if(status != 0)
                {
                    Serial.print("Wire.requestFrom() failed with status ");
                    Serial.println((long)status);
                }
                else
                {
                    bytesAvail = Wire.available();
                    if(bytesAvail != 1)
                    {
                        Serial.print("Wire.available() returned less number of bytes: ");
                        Serial.println((long)status);
                    }
                    else
                    {
                        i2cRdBuf[0] = Wire.read();

                        Serial.print("Value read is ");
                        Serial.println((long)i2cRdBuf[0]);

                        if(i2cRdBuf[0] == value)
                        {
                            Serial.println("Written value matching with read value!!! \n");
                        }
                        else
                        {
                            Serial.println("Written value not matching with read value!!! \n");
                        }
                    }
                }
            }
        }
    }
}

void setup()
{
    Serial.println("Wire library example\n");

    codecFunc(0, 0);

    codecFunc(65, 81);

    codecFunc(66, 99);

    codecFunc(0, 1);

    codecFunc(51, 0x28);

    codecFunc(52, 0x3c);

    Serial.print("Wire example completed!!!");
}

void loop()
{
}
