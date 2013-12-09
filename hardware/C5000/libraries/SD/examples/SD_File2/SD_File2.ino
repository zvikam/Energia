/*
  Test case to verify SD APIs for Directory
  
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
  6. In the first part of this example, 5 files are created and some data is
     written in these files.
  7. In the second part, a file handle to the root directory is obtained. The
     contents of the root directory are queried and are displayed on the serial
     port.
*/

#include "SD.h"

void setup()
{
    Bool retStatus;
    int  noOfBytesWritten;
    int  index;
    File parentDirHandle;
    File childHandle;
    char fileName[13];
    char writeBuffer[50];

    Serial.println("SD Module Example 2: File Operations");

    retStatus = SD.begin();
    if (TRUE == retStatus)
    {
        Serial.println("\r\nSuccessful in Initializing the SD Module");

        for (index = 0; index < 5; index++)
        {
            sprintf (fileName, "dir%d.txt", index);
            sprintf (writeBuffer, "dir%d.txt: File of Directory Browsing Example", index);

            childHandle = SD.open(fileName, FILE_WRITE);
            if (childHandle)
            {
                noOfBytesWritten = childHandle.print(writeBuffer);
	        	childHandle.close();

                if (0 == noOfBytesWritten)
                {
	                Serial.println("Error In Writing to the file");
	                return;
                }
            }
            else
            {
                Serial.println("\r\nError in Opening the file");
            }
        }

        parentDirHandle = SD.open("/");
        if (parentDirHandle)
        {
            Serial.println("\r\nOpening the root directory Successful");
            Serial.println("Contents of the Root Directory are: \r\n");

            while (1)
            {
                childHandle = parentDirHandle.openNextFile();
                if (childHandle)
                {
                    if (childHandle.isDirectory())
                    {
                        Serial.println("Directory:");
                        childHandle.getName(fileName);
                        Serial.print("Name: ");
                        Serial.println(fileName);
                    }
                    else
                    {
                        Serial.println("File:");
                        childHandle.getName(fileName);
                        Serial.print("Name: ");
                        Serial.println(fileName);
                        Serial.print("Size: ");
                        Serial.print((long)childHandle.size());
                        Serial.println(" Bytes");
                    }
	                childHandle.close();
                }
                else
                {
                    Serial.println("\r\nNo more Files Under the directory");
                    break;
                }
            }
        }
        else
        {
            Serial.println("\r\nError in Opening the root directory");
        }
    }
    else
    {
        Serial.println("\r\nError in Initializing SD Module");
    }

    Serial.println("\r\nEnd of SD Module Example 2");
}

void loop()
{

}
