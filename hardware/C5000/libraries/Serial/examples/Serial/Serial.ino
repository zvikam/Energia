/*
  Test case to verify Serial APIs

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Follow the instructions displayed on the Serial Monitor.
*/

void setup()
{
    Bool  result;
    char  testString[50];
    float floatVal;
    long  longVal;
    char  charVal;

    Serial.println("Program for testing Serial APIs");

    Serial.println("===============================");

    /* Test for find(char *target) and readBytes(char *buffer, int length) APIs */
    Serial.println("Test for find(char *target) and readBytes(char *buffer, int length) APIs");

    Serial.println("Enter the string to find (4 characters):");
    Serial.readBytes(testString, 4);

    testString[4] = '\0';

    Serial.println("Enter string in which the previous string should be looked for");
    result = Serial.find(testString);
    if(result == TRUE)
    {
        Serial.println("String found");
    }
    else
    {
        Serial.println("Timeout; string not found");
    }

    /* Test for findUntil(char *target) and readBytes(char *buffer, int length) APIs */
    Serial.println("Test for findUntil(char *target) and readBytes(char *buffer, int length) APIs");

    Serial.println("Enter the string to find (4 characters):");
    Serial.readBytes(testString, 4);

    testString[4] = '\0';

    Serial.println("Enter string in which the previous string should be looked for. Enter '$' to stop.");
    result = Serial.findUntil(testString, "$");
    if(result == TRUE)
    {
        Serial.println("String found");
    }
    else
    {
        Serial.println("Timeout; string not found");
    }

    /* Test for parseFloat(void) and println(float value) APIs */
    Serial.println("Test for parseFloat(void) and println(float value) APIs");

    Serial.println("Enter a float value ending with an alphabet (eg: 1.23a):");
    floatVal = Serial.parseFloat();

    Serial.print("The value you entered is ");
    Serial.println(floatVal);

    /* Test for parseInt(void) and println(long value) APIs */
    Serial.println("Test for parseFloat(void) and println(float value) APIs");

    Serial.println("Enter a integer value ending with an alphabet (eg: 234a):");
    longVal = Serial.parseInt();

    Serial.print("The value you entered is ");
    Serial.println(longVal);

    /* Test for print(long value) API */
    Serial.println("Test for print(long value) API");
    Serial.println("Output should be 123450");
    longVal = 123450;
    Serial.print(longVal);
    Serial.println(" ");

    /* Test for print(float value) API */
    Serial.println("Test for print(float value) API");
    Serial.println("Output should be 405.23");
    floatVal = 405.23;
    Serial.print(floatVal);
    Serial.println(" ");

    /* Test for print(char value) API */
    Serial.println("Test for print(float value) API");
    Serial.println("Output should be 'C'");
    charVal = 'C';
    Serial.print(charVal);
    Serial.println(" ");

    /* Test for print(char *printString) API */
    Serial.println("Test for print(char *printString) API");
    Serial.println("Output should be 'Test'");
    testString[0] = 'T';
    testString[1] = 'e';
    testString[2] = 's';
    testString[3] = 't';
    testString[4] = '\0';
    Serial.print(testString);
    Serial.println(" ");

    /* Test for print(long value, int format) API with BINARY FORMAT */
    Serial.println("Test for print(long value, int format) API with BINARY FORMAT");
    Serial.println("Output should be 1111000");
    longVal = 120;
    Serial.print(longVal, BIN);
    Serial.println(" ");

    /* Test for print(long value, int format) API with DECIMAL FORMAT */
    Serial.println("Test for print(long value, int format) API with DECIMAL FORMAT");
    Serial.println("Output should be 365");
    longVal = 0x16D;
    Serial.print(longVal, DEC);
    Serial.println(" ");

    /* Test for print(long value, int format) API with OCTAL FORMAT */
    Serial.println("Test for print(long value, int format) API with OCTAL FORMAT");
    Serial.println("Output should be 170");
    longVal = 120;
    Serial.print(longVal, OCT);
    Serial.println(" ");

    /* Test for print(long value, int format) API with HEXADECIMAL FORMAT */
    Serial.println("Test for print(long value, int format) API with HEXADECIMAL FORMAT");
    Serial.println("Output should be 0x17F1B");
    longVal = 98075;
    Serial.print(longVal, HEX);
    Serial.println(" ");

    /* Test for print(float value, int noOfDecDigits) API */
    Serial.println("Test for print(float value, int noOfDecDigits) API");
    Serial.println("Output should be 10.3403");
    floatVal = 10.340354;
    Serial.print(floatVal, 4);
    Serial.println(" ");

    /* Test for println(long value) API */
    Serial.println("Test for println(long value) API");
    Serial.println("Output should be 123450");
    longVal = 123450;
    Serial.println(longVal);

    /* Test for println(float value) API */
    Serial.println("Test for println(float value) API");
    Serial.println("Output should be 405.23");
    floatVal = 405.23;
    Serial.println(floatVal);

    /* Test for println(char character) API */
    Serial.println("Test for println(float value) API");
    Serial.println("Output should be 'C'");
    charVal = 'C';
    Serial.println(charVal);

    /* Test for println(char *printString) API */
    Serial.println("Test for println(char *printString) API");
    Serial.println("Output should be 'Test'");
    testString[0] = 'T';
    testString[1] = 'e';
    testString[2] = 's';
    testString[3] = 't';
    testString[4] = '\0';
    Serial.println(testString);

    /* Test for println(long value, int format) API with BINARY FORMAT */
    Serial.println("Test for println(long value, int format) API with BINARY FORMAT");
    Serial.println("Output should be 1111000");
    longVal = 120;
    Serial.println(longVal, BIN);

    /* Test for println(long value, int format) API with DECIMAL FORMAT */
    Serial.println("Test for println(long value, int format) API with DECIMAL FORMAT");
    Serial.println("Output should be 365");
    longVal = 0x16D;
    Serial.println(longVal, DEC);

    /* Test for println(long value, int format) API with OCTAL FORMAT */
    Serial.println("Test for println(long value, int format) API with OCTAL FORMAT");
    Serial.println("Output should be 170");
    longVal = 120;
    Serial.println(longVal, OCT);

    /* Test for println(long value, int format) API with HEXADECIMAL FORMAT */
    Serial.println("Test for println(long value, int format) API with HEXADECIMAL FORMAT");
    Serial.println("Output should be 0x17F1B");
    longVal = 98075;
    Serial.println(longVal, HEX);

    /* Test for println(float value, int noOfDecDigits) API */
    Serial.println("Test for println(float value, int noOfDecDigits) API");
    Serial.println("Output should be 10.3403");
    floatVal = 10.340354;
    Serial.println(floatVal, 4);

    /* Test for read(void) and write(int value) APIs */
    Serial.println("Test for read(void) and write(int value) APIs");
    Serial.println("Enter a Character (1 byte):");
    charVal = Serial.read();
    Serial.print("You entered: ");
    Serial.println(charVal);

    /* Test for readBytes(char *buffer, int length) and write(char *string, int length) APIs */
    Serial.println("\r\nTest for readBytes(char *buffer, int length) and write(char *string, int length) APIs");
    Serial.println("Enter a string of length 4 bytes:");
    Serial.readBytes(testString, 4);
    Serial.print("You entered ");
    Serial.write(testString, 4);

    /* Test for readBytesUntil(char termChar, char *buffer, int length) and write(char *string) APIs */
    Serial.println("\r\nTest for readBytesUntil(char termChar, char *buffer, int length) and write(char *string) APIs");
    Serial.println("Enter a string of maximum length 50 bytes. Press '$' to stop:");
    Serial.readBytesUntil('$', testString, 50);
    Serial.print("You entered ");
    Serial.write(testString);

    Serial.println("\r\n");
    Serial.println("End of Serial Example!!");

    Serial.end();
}

void loop()
{

}
