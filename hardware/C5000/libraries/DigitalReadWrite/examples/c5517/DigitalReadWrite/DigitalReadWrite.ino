/*
  Digital Read Write
  Toggles the states of LED0 and LED1 continuously in a loop.

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the messages displayed on the Serial Monitor.
*/

void setup() {
    Serial.println(" ");
    Serial.println("Digital ReadWrite Test!!");

    Serial.println(" ");
    Serial.println("This Example Toggles LED0 and LED1 continuously");
}

void loop() {
    int        status;
    static int ledValue = 0;

    /* Set LED0 as OUPUT */
    status = pinMode(LED0, 1);
    if(status != 0)
    {
        Serial.println("pinMode for LED0 failed");
    }

    /* Write a value to the LED0 */
    status = digitalWrite(LED0, ledValue);
    if (status != 0)
    {
        Serial.println("digitalWrite failed for LED0");
    }

    ledValue++;
    ledValue = ledValue % 2;

    /* Set LED1 as OUPUT */
    status = pinMode(LED1, 1);
    if(status != 0)
    {
        Serial.println("pinMode for LED1 failed");
    }

    /* Write a value to the LED1 */
    status = digitalWrite(LED1, ledValue);
    if (status != 0)
    {
        Serial.println("digitalWrite failed for LED1");
    }

    delay(1000); /* Giving a delay of 1sec between toggling */
}
