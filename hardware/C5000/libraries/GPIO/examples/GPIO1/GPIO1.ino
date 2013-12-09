/*
  GPIO Read Write
  Configures GPIO12 as input pin and GPIO13 as output pin.
  Both the GPIO pins (pin16 and pin18 on P2)need to be shorted to check the functionality of the module.
  Set/Reset the output pin(GPIO13) P2 pin16 and read the value of input pin (GPIO12) P2 pin18 and compare both values.
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

    Serial.println("GPIO Test!!");
    Serial.println("Short pin16 and pin18 on port P2 for the test");

    // Set mode for GPIO12 - Configures GPIO pin muxing
    status = gpioSelectMode(DSP_GPIO12);
    if(status != 0)
    {
        Serial.println("Set mode for GPIO12 failed");
    }

    // Set mode for GPIO13
    status = gpioSelectMode(DSP_GPIO13);
    if(status != 0)
    {
        Serial.println("GPIO mode configuration for GPIO13 failed");
    }

    // Configure GPIO12 as input pin
    status = gpioPinMode(DSP_GPIO12, INPUT);
    if(status != 0)
    {
        Serial.println("GPIO mode configuration for GPIO12 failed");
    }

    // Configure GPIO13 as output pin
    status = gpioPinMode(DSP_GPIO13, OUTPUT);
    if(status != 0)
    {
         Serial.println("GPIO mode configuration for GPIO13 failed");
    }
    // Get pin direction of GPIO12
    pinDirection = gpioGetDirection(DSP_GPIO12);
    if(pinDirection == INPUT)
    {
        Serial.println("GPIO mode configuration of GPIO12 is INPUT");
    }
    else
    {
        Serial.println("GPIO mode configuration of GPIO12 failed");
        Serial.println((long)pinDirection);
    }

    // Get pin direction of GPIO13
    pinDirection = gpioGetDirection(DSP_GPIO13);
    if(pinDirection == OUTPUT)
    {
        Serial.println("GPIO mode configuration of GPIO13 is OUTPUT");
    }
    else
    {
        Serial.println("GPIO mode configuration of GPIO13 failed");
        Serial.println((long)pinDirection);
    }
}

void loop() {
    unsigned int gpioState;

    // GPIO set test
    gpioWrite(DSP_GPIO13, HIGH);          // set the output pin
    gpioState = gpioRead(DSP_GPIO12);    // read the input pin

    if(gpioState == HIGH)
    {
        Serial.println("GPIO set test passed");
    }
    else
    {
        Serial.println("GPIO set test failed");
    }

    delaySeconds(1);              // wait for a second

    // GPIO reset test
    gpioWrite(DSP_GPIO13, LOW);          // set the output pin
    gpioState = gpioRead(DSP_GPIO12);    // read the input pin

    if(gpioState == LOW)
    {
        Serial.println("GPIO reset test passed  ");
    }
    else
    {
        Serial.println("GPIO reset test failed  ");
    }

    delaySeconds(1);              // wait for a second
}
