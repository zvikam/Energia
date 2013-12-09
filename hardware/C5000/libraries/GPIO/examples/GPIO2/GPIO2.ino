/*
  GPIO set/reset
  Configures GPIO14 as output pin.
  Set/Reset the output pin(GPIO14) P2 pin20 and read back the value of the pin
  and compare value read with the value set.
  If both the values match, then the test passes.

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the messages displayed on the Serial Monitor.
*/

void setup() {
    unsigned short status;
    int            pinDirection;
    unsigned int   gpioState;

    // Set mode for GPIO14 - Configures GPIO pin muxing
    status = gpioSelectMode(DSP_GPIO14);
    if(status != 0)
    {
        Serial.println("Set mode for GPIO14 failed");
    }

    // Configure GPIO14 as output pin
    status = gpioPinMode(DSP_GPIO14, OUTPUT);
    if (status != 0)
    {
        Serial.println("GPIO mode configuration for GPIO14 failed");
    }

    // Get pin direction of GPIO14
    pinDirection = gpioGetDirection(DSP_GPIO14);
    if(pinDirection == OUTPUT)
    {
        Serial.println("GPIO mode configuration of GPIO14 is OUTPUT");
    }
    else
    {
        Serial.println("GPIO get configuration of GPIO14 fails");
        Serial.println((long)pinDirection);
    }

    gpioWrite(DSP_GPIO14, HIGH);          // set the output pin
    gpioState = gpioRead(DSP_GPIO14);    // read the input pin

    if(gpioState == HIGH)
    {
       Serial.println("GPIO set test passed");
    }
    else
    {
       Serial.println("GPIO set test failed");
    }

    // GPIO reset test
    gpioWrite(DSP_GPIO14, LOW);          // set the output pin
    gpioState = gpioRead(DSP_GPIO14);    // read the input pin

    if(gpioState == LOW)
    {
        Serial.println("GPIO reset test passed  ");
    }
    else
    {
        Serial.println("GPIO reset test failed  ");
    }
}

void loop() {

}
