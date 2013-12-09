/*
  Example sketch which searches for the .wav files on the SD Card and opens
  them. It then reads data from the wave files present on the SD Card and sends
  the data to codec, which can be listened on headphone.

  Procedure:
  1. Copy few wave file with extension .wav to SD card
  2. Connect Arduino to host PC using USB cable.
  3. Verify and Upload the example binary to DSP shield.
  4. Connect head phone to green jack of DSP shield.
  5. Open Serial Monitor and connect to the Arduino Uno COM port.
  6. Set the baud rate to 9600.
  7. Observe the messages displayed on the Serial Monitor.
  8. Listen to the audio from head phone.
*/

#include "SD.h"
#include "Audio.h"
#include "OLED.h"

#define BUFFER_SIZE (27u)

char writeBuffer[BUFFER_SIZE];

File rootDirHandle;
File fileHandle;

bool bufferRead = false;
bool bufferSent = true;
bool stopExample = false;

unsigned int noOfChannels;

Uint16 audioReadBufferL[I2S_DMA_BUF_LEN];
Uint16 audioReadBufferR[I2S_DMA_BUF_LEN];
char readBuf[4 * I2S_DMA_BUF_LEN] = {0};

interrupt void dmaIsr(void)
{
    Uint16 ifrValue;

    /* Read the DMA interrupt */
    ifrValue = DMA.readInterruptStatus();

    if ((ifrValue >> DMA_CHAN_ReadR) & 0x01)
    {
        if (bufferRead) //if there is a buffer ready, read it out.
        {
            bufferCopy();
        }
    }
    AudioC.isrDma();
}

int openWavFile(void)
{
    char fileName[13];
    int  index;
    char readChar;

    while (1)
    {
        fileHandle = rootDirHandle.openNextFile();
        if (fileHandle)
        {
            if (!(fileHandle.isDirectory()))
            {
                fileHandle.getName(fileName);

                index = strlen(fileName);

                if (((fileName[index - 3] == 'w') || (fileName[index - 3] == 'W')) &&
                    ((fileName[index - 2] == 'a') || (fileName[index - 2] == 'A')) &&
                    ((fileName[index - 1] == 'v') || (fileName[index - 1] == 'V')))
                {
                    disp.clear(1);
                    disp.setline(1);
                    disp.print(fileName);

                    Serial.print("\nFile Name: ");
                    Serial.println(fileName);
                    Serial.print("Reading WAVE file header: ");
                    for (index = 0; index < 4; index++)
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

                    fileHandle.seek(22);

                    Serial.print("\r\nNumber of Channels: ");
                    noOfChannels = (unsigned int)fileHandle.read();
                    Serial.print((int)noOfChannels);
                    if (1 == noOfChannels)
                    {
                        Serial.println(" (Mono)");
                    }
                    else
                    {
                        Serial.println(" (Stereo)");
                    }

                    fileHandle.seek(44);
                    return (0);
                }
            }
        }
        else
        {
            disp.setline(1);
            disp.clear(1);
            disp.print("Stopped");
            return (1);
        }
    }
}

void setup()
{
    int  retStatus;

    Serial.print("\n Audio Player TEST!\n");

    pinMode(LED0, OUTPUT);

    disp.oledInit();
    disp.clear();
    disp.setOrientation(1);
    disp.setline(0);
    disp.print("Audio Player");

    retStatus = SD.begin(); //initialize SD Card
    if (TRUE == retStatus) // if init okay
    {
        Serial.println("\r\nSuccessful in Initializing the SD Module");

        rootDirHandle = SD.open("/");
        if (rootDirHandle)
        {
            retStatus = openWavFile();

            if (0 != retStatus)
            {
                Serial.println("\r\nWave files are not present on the SD Card");
                stopExample = true;
            }
        }
        else
        {
            Serial.println("\r\nError in Opening Root Directory");
        }
    }
    else
    {
        Serial.println("\r\nError in Initializing SD Module");
    }

    retStatus = AudioC.Audio();
    if (retStatus != 0)
    {
        Serial.print("\n Audio Init failed!\n");
    }

    AudioC.attachIntr((INTERRUPT_IsrPtr)dmaIsr);
}

void bufferCopy() // simple copy from the read buffer.
{
    int index;
    for (index = 0; index < I2S_DMA_BUF_LEN; index++)
    {
        AudioC.audioInLeft[AudioC.activeInBuf][index] = audioReadBufferL[index];
        AudioC.audioInRight[AudioC.activeInBuf][index] = audioReadBufferR[index];
    }
    bufferSent = true;
    bufferRead = false;
}

void loop()
{
    int bytesRead;
    int index;
    int index2;
    int status;
    Uint16 sampleData;

    if ((stopExample == false) && (bufferSent == true))
    {
        index2 = 0;

        if (2 == noOfChannels) /* Stereo */
        {
            bytesRead = fileHandle.read(readBuf, 4 * I2S_DMA_BUF_LEN);
		}
		else
		{
			bytesRead = fileHandle.read(readBuf, 2 * I2S_DMA_BUF_LEN);
		}
        /* In theory, set this to four and you should get both channels at once
           https://ccrma.stanford.edu/courses/422/projects/WaveFormat/ this
           doesn't seem to be the case */

        if (0 == bytesRead)
        {
            /* Open next wave file, if present on the SD card */
            status = openWavFile();
            if (0 != status)
            {
                Serial.println("\r\nNo more Wave files present on the SD Card");
                stopExample = true;
            }
            return;
        }

        for (index = 0; index < I2S_DMA_BUF_LEN; index++)
        {
            sampleData = readBuf[index2+1]<<8|readBuf[index2+2];
            audioReadBufferL[index] = sampleData;

            if (2 == noOfChannels) /* Stereo */
            {
                sampleData = readBuf[index2+3]<<8|readBuf[index2+4];
                index2 += 4;
            }
            else
            {
                index2 += 2;
            }

            audioReadBufferR[index] = sampleData;
        }
        bufferSent = false;
        bufferRead = true;
    }
}
