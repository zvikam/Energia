/*
  OLED and Serial Library Example

  Reads Messages from the Serial port and Displays on the LCD

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the output on Serial Monitor and LCD screen

  Note: 1. Length of Messages is limited to 12 characters because of the LCD
           size
        2. If the User wants to send a message lesser than 12 characters, enter
           '$' at the end of the message.
*/

#include <OLED.h>

#define MSG_LENGTH (12)

void setup() {
    Serial.println("\n LCD TEST!");

    Serial.print("Enter Messages of Max 12 characters or enter '$' at the ");
    Serial.print("end of the message, to display a message of length lesser ");
    Serial.println("than 12 characters");

    disp.oledInit();
    disp.setline(0);
    disp.setOrientation(1);
    disp.clear();
}

void loop() {
    char readChar;
    int  index;
    char dispString[MSG_LENGTH + 1];

    Serial.println("\r\nEnter the message which is to be displayed on the LCD");

    index = 0;
    do
    {
		readChar = Serial.read();
		dispString[index++] = readChar;
	} while ((readChar != '$') && (index < MSG_LENGTH));

    if (readChar == '$')
    {
		dispString[index - 1] = '\0';
	}

    Serial.print("The message entered is: ");
    Serial.println(dispString);

    Serial.println("Displaying message on LCD");
    disp.clear();
    disp.print(dispString);
}
