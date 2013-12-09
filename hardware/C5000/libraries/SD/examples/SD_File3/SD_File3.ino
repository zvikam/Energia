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
  6. In this example a file handle to the root directory is obtained. The
     contents of the root directory and its subsequent sub-directories are
     queried recursively and are displayed on the serial port.
*/

#include "SD.h"

void displayContents(void *dirHandle)
{
    File *parentDirHandle;
    File childHandle;
    int  fileCount;
    int  dirCount;

    parentDirHandle = (File *)dirHandle;
    fileCount       = 0;
    dirCount        = 0;

    while (1)
    {
        childHandle = parentDirHandle->openNextFile();
        if (childHandle)
        {
            if (childHandle.isDirectory())
            {
                Serial.print("\r\nDirectory Found--- '");
                Serial.print(childHandle.fileName);
                Serial.println("'");
                Serial.print("Contents of the Directory: '");
                Serial.print(childHandle.fileName);
                Serial.println("' are:");
                displayContents((void *)&childHandle);
                dirCount++;
            }
            else
            {
                Serial.print("File Found---   Name: ");
                Serial.print(childHandle.fileName);
                Serial.print("\tSize: ");
                Serial.print((long)childHandle.size());
                Serial.println(" Bytes");
                fileCount++;
            }
            childHandle.close();
        }
        else
        {
            Serial.print("\r\nNo more Files Under the directory '");
            Serial.print(parentDirHandle->fileName);
            Serial.println("'");
            Serial.print("File Count: ");
            Serial.print((long)fileCount);
            Serial.print("   Dir Count: ");
            Serial.println((long)dirCount);
            Serial.println(" ");
            break;
        }
    }
}

void setup()
{
    Bool retStatus;
    File parentDirHandle;

    Serial.println("SD Module Example 3: Directory Browsing");

    retStatus = SD.begin();
    if (TRUE == retStatus)
    {
        Serial.println("\r\nSuccessful in Initializing the SD Module");

        parentDirHandle = SD.open("/");
        if (parentDirHandle)
        {
            Serial.println("\r\nOpening the root directory Successful");
            Serial.println("Contents of the Root Directory are: \r\n");

            displayContents((void *)&parentDirHandle);
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

    parentDirHandle.close();
    Serial.println("\r\nEnd of SD Module Example 3");
}

void loop()
{

}
