/*
  Digital Read Write
  Toggles the states of LED0, LED1 and LED2 continuously in a loop.

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the messages displayed on the Serial Monitor.
  6. Observe the toggling of ON/OFF states for LED0, LED1 and LED2
*/

void setup() {
    Serial.println(" ");
    Serial.println("Digital ReadWrite Test!!");

    Serial.println(" ");
    Serial.println("This Example Toggles LED0, LED1 and LED2 continuously");
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

    /* Set LED1 as OUPUT */
    status = pinMode(LED1, 1);
    if(status != 0)
    {
        Serial.println("pinMode for LED1 failed");
    }

    /* Set LED2 as OUPUT */
    status = pinMode(LED2, 1);
    if(status != 0)
    {
        Serial.println("pinMode for LED2 failed");
    }

    /* Write a value to the LED0 */
    status = digitalWrite(LED0, !ledValue); /* On, if ledValue == 0 */
    if (status != 0)
    {
        Serial.println("digitalWrite failed for LED0");
    }

    /* Write a value to the LED1 */
    status = digitalWrite(LED1, ledValue % 2); /* On, if ledValue == 1 */
    if (status != 0)
    {
        Serial.println("digitalWrite failed for LED1");
    }

    /* Write a value to the LED2 */
    status = digitalWrite(LED2, ledValue / 2); /* On, if ledValue == 2 */
    if (status != 0)
    {
        Serial.println("digitalWrite failed for LED2");
    }

    delay(1000); /* Giving a delay of 1sec between toggling */

    if (2 == ledValue)
    {
        /* Toggling LED2 to Off, for clear toggling from LED2 to LED0 */
        status = digitalWrite(LED2, 0);
    }

    ledValue++;
    ledValue = ledValue % 3;
}
