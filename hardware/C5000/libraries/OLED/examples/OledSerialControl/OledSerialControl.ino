/*
  OLED Library

  Program which gives a menu list to the User to try out the different OLED
  APIs

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Select the options desired, displayed in the Menu List
  6. Observe the output on Serial Monitor and LCD screen
*/

#include <OLED.h>

void setup() {
    int  stopPgm;
    int  userOption;
    char displayStr[13];

    Serial.println("\n OLED Library APIs TEST!");

    disp.oledInit();
    disp.clear();
    disp.setline(0);
    disp.setOrientation(1);

    stopPgm = 0;
    while (0 == stopPgm)
    {
        Serial.println(" ");
        Serial.println("----------------------------------");
        Serial.println("            OLED MENU             ");
        Serial.println("----------------------------------");
        Serial.println("00: Display a string in Line 0");
        Serial.println("01: Display a string in Line 1");
        Serial.println("02: Scroll Line 0 to Left");
        Serial.println("03: Scroll Line 0 to Right");
        Serial.println("04: Scroll Line 1 to Left");
        Serial.println("05: Scroll Line 1 to Right");
        Serial.println("06: Scroll both Line 0 & 1 to Left");
        Serial.println("07: Scroll both Line 0 & 1 to Right");
        Serial.println("08: To Stop Scrolling");
        Serial.println("09: To Flip");
        Serial.println("10: To Clear Line 0");
        Serial.println("11: To Clear Line 1");
        Serial.println("12: To Clear Screen");
        Serial.println("13: To exit");
        Serial.println("----------------------------------");
        Serial.println("Enter your choice");

        userOption = Serial.read() - '0';
        userOption *= 10;
        userOption += Serial.read() - '0';
        Serial.print("Option Entered: ");
        Serial.print((long)userOption);
        Serial.println("\r\n");

        switch (userOption)
        {
            case 0:
            case 1:
                disp.noAutoscroll();
                disp.clear(userOption);
                Serial.println("\r\nEnter the String (Max 12 characters or enter '$' at the end)");
                Serial.readBytesUntil('$', displayStr, 12);
                disp.setline(userOption);
                disp.print(displayStr);
                break;

            case 2:
                disp.scrollDisplayLeft(0);
                break;

            case 3:
                disp.scrollDisplayRight(0);
                break;

            case 4:
                disp.scrollDisplayLeft(1);
                break;

            case 5:
                disp.scrollDisplayRight(1);
                break;

            case 6:
                disp.scrollDisplayLeft();
                break;

            case 7:
                disp.scrollDisplayRight();
                break;

            case 8:
                disp.noAutoscroll();
                break;

            case 9:
                disp.flip();
                break;

            case 10:
                disp.clear(0);
                break;

            case 11:
                disp.clear(1);
                break;

            case 12:
                disp.clear();
                break;

            case 13:
                Serial.println("Exiting the Program");
                stopPgm = 1;
                break;

            default:
                Serial.println("Invalid option!!");
                break;

        }
    }

    Serial.println("\r\n OLED Library APIs TEST Done!");
}

void loop() {
}