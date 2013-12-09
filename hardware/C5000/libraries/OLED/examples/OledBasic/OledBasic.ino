/*
  OLED Library

  Displays WELCOME and DSP SHIELD on two lines

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the output on Serial Monitor and LCD screen
*/

#include <OLED.h>

void setup() {

	Serial.print("\n LCD TEST!\r\n");

        disp.oledInit();
        Serial.print("\n OLED INIT Done!\r\n");
        disp.clear();
        Serial.print("\n OLED clear screen Done!\r\n");
        disp.setline(0);
        Serial.print("\n OLED set line Done!\r\n");
        disp.setOrientation(1);
        Serial.print("\n OLED set orientation Done!\r\n");
        disp.print("Welcome");

        disp.setline(1);
        disp.print("DSP SHIELD");
        Serial.print("\n OLED print string is done \r\n");
        disp.scrollDisplayRight();
        Serial.print("\n OLED display is scrolling Right \r\n");
        delaySeconds(10);
        disp.clear(0);
        Serial.print("\n OLED display is cleared for page0 \r\n");
        delaySeconds(2);
        disp.clear(1);
        Serial.print("\n OLED display is cleared for page1 \r\n");
        Serial.print("\n LCD TEST Done!\r\n");
}

void loop() {
}