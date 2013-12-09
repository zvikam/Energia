/*
  Test case to verify SD File APIs

Note: SD Library requires SD card to be formatted in a specific
         format for proper operation. It is recommended to use
         SD formatter from SD card org or HP format tool for
         formatting the SD card

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the Messages displayed on the Serial Monitor.
  6. In the first part of this example a buffer of length 26(filled with
     alphabets A-Z) is written, then a single char 'N' is written and finally
     an integer '12345' is written.
  7. In the second part, the above written contents are read back, and
     displayed on the serial port.
*/

#include "SD.h"

#define BUFFER_SIZE (27u)

char writeBuffer[BUFFER_SIZE];

void setup()
{
    Bool          retStatus;
    int           noOfBytesWritten;
    int           index;
    File          fileHandle;
    unsigned long fileSize;
    char          readChar;

    Serial.println("SD Module Example 1: File Operations");

    retStatus = SD.begin();
    if (TRUE == retStatus)
    {
        Serial.println("\r\nSuccessful in Initializing the SD Module");

        fileHandle = SD.open("demo.txt", FILE_WRITE);
        if (fileHandle)
        {
            for (index = 0; index < BUFFER_SIZE - 1; index++)
            {
                writeBuffer[index] = 'A' + index;
            }
            writeBuffer[index] = '\0';

            /* Writing a String to the File */
            noOfBytesWritten = fileHandle.print(writeBuffer);
            if (0 == noOfBytesWritten)
            {
                Serial.println("Error In Writing a String to the file");
                fileHandle.close();
                return;
            }

            Serial.println("\r\nWriting a String to the file Successful");
            fileSize  = fileHandle.size();

            Serial.print("Size of the file after Writing the String is: ");
            Serial.println((long)fileSize);

            /* Writing a Character to the File */
            noOfBytesWritten = fileHandle.print((char)'N');
            if (0 == noOfBytesWritten)
            {
                Serial.println("Error In Writing a character 'N' to the file");
                fileHandle.close();
                return;
            }

            Serial.println("\r\nWriting a Character 'N' to the file Successful");
            fileSize  = fileHandle.size();

            Serial.print("Size of the file after Writing the character 'N' is: ");
            Serial.println((long)fileSize);

            /* Writing an Integer to the File */
            noOfBytesWritten = fileHandle.print(12345);
            if (0 == noOfBytesWritten)
            {
                Serial.println("Error In Writing an Integer to the file");
                fileHandle.close();
                return;
            }

            Serial.println("\r\nWriting an Integer '12345' to the file Successful");
            fileSize  = fileHandle.size();

            Serial.print("Size of the file after Writing the integer '12345' is: ");
            Serial.println((long)fileSize);

            fileHandle.seek(0);
            Serial.println("\r\nThe contents of the file are:");
            for (index = 0; index < fileSize; index++)
            {
                readChar = fileHandle.read();
                if (-1 == readChar)
                {
                    Serial.println("\r\nError in reading from the file");
                }
                else
                {
                    Serial.print((char)readChar);
                }
            }

            fileHandle.close();
            Serial.println("\r\nFile Close successful");
        }
        else
        {
            Serial.println("\r\nError in Opening the file");
        }
    }
    else
    {
        Serial.println("\r\nError in Initializing SD Module");
    }

    Serial.println("\r\nEnd of SD Module Example 1");
}

void loop()
{

}
