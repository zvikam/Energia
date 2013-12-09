/*
  OLED Library

  Program to demonstrate the Use of all print APIs of OLED library used for
  Displaying

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the output on Serial Monitor and LCD screen
*/

#include <OLED.h>

void setup() {

    Serial.println("\r\nLCD Print API TEST!");

    disp.oledInit();
    disp.setOrientation(1);

    disp.clear();
    Serial.println("\r\nDisplaying a String on the LCD");
    disp.setline(0);
    disp.print("Dsp Shield");
    delaySeconds(5);

    disp.clear();
    Serial.println("\r\nDisplaying a Character 'M' on the LCD");
    disp.setline(0);
    disp.print('M');
    delaySeconds(5);

    disp.clear();
    Serial.println("\r\nDisplaying an integer value '1234567' on the LCD");
    disp.setline(0);
    disp.print((long)1234567);
    delaySeconds(5);

    disp.clear();
    Serial.println("\r\nDisplaying Hexadecimal equivalent of '1234567' on the LCD");
    disp.setline(0);
    disp.print((long)1234567, HEXADECIMAL);
    delaySeconds(5);

    disp.clear();
    Serial.println("\r\nDisplaying Octal equivalent of '1234567' on the LCD");
    disp.setline(0);
    disp.print((long)1234567, OCTAL);
    delaySeconds(5);

    disp.clear();
    Serial.println("\r\nDisplaying Binary equivalent of '123' on the LCD");
    disp.setline(0);
    disp.print((long)123, BINARY);

    Serial.println("\r\nLCD Print API TEST Done!");
}

void loop() {
}