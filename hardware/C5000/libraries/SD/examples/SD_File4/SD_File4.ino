/*
  Test case to verify SD APIs for File Operations, Directory Creation and
  Browsing

Note: SD Library requires SD card to be formatted in a specific
         format for proper operation. It is recommended to use
         SD formatter from SD card org or HP format tool for
         formatting the SD card

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Send any character using keyboard.
  6. Observe the Messages displayed on the Serial Monitor.
  7. In the first part of this example, a directory path 'DIR1/DIR2/DIR3/DIR4
     /DIR5' is created.
  8. In the second part, 4 files are created under each directory in the
     directory path 'DIR1/DIR2/DIR3/DIR4/DIR5' and some data is written in these
     files.
  9. In the third part, a file handle to the root directory is obtained. The
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

void createFiles()
{
    int  indexI;
    int  indexJ;
    int  noOfBytesWritten;
    char writeBuffer[50];
    char fileName[50];
    char filePath[50];
    File childHandle;
    int  counter;

    filePath[0] = '\0';
    counter = 1;
    for (indexI = 0; indexI < 5; indexI++)
    {
		sprintf(filePath, "%sDIR%d/", filePath, (indexI + 1));
        for (indexJ = 0; indexJ < 4; indexJ++)
        {
            sprintf (fileName, "%sdir%d.txt", filePath, counter);
            sprintf (writeBuffer, "dir%d.txt: File under directory DIR%d", counter, (indexI + 1));

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
                counter++;
            }
            else
            {
                Serial.println("\r\nError in Opening/Creating the file");
            }
        }
    }
}

void setup()
{
    Bool retStatus;
    File parentDirHandle;

    Serial.println("SD Module Example 4: Directory Creation & Browsing Example");

    retStatus = SD.begin();
    if (TRUE == retStatus)
    {
        Serial.println("\r\nSuccessful in Initializing the SD Module");

        retStatus = SD.mkdir("DIR1/DIR2/DIR3/DIR4/DIR5");
        if (TRUE == retStatus)
        {
            Serial.println("\r\nCreating the Directories Successful");
        }
        else
        {
            Serial.println("\r\nError in Creating the Directories");
            return;
        }

        createFiles();

        parentDirHandle = SD.open("/");
        if (parentDirHandle)
        {
            Serial.println("\r\nOpening the Root directory Successful");
            Serial.println("Contents of the Root Directory are: \r\n");

            displayContents((void *)&parentDirHandle);
            parentDirHandle.close();
        }
    }
    else
    {
        Serial.println("\r\nError in Initializing the SD Module");
    }

    Serial.println("\r\nEnd of SD Module Example 4");
}

void loop()
{

}
