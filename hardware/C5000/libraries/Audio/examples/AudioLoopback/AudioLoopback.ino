/*
  Example sketch for Audio demo. Audio library reads data from
  codec audio IN and sends the data to codec which can be listened
  on headphone.
  
  For any data processing on audio data, use the pointers 
  AudioC.audioInLeft and AudioC.audioInRight. Audio data will
  be available in these buffers when dmaIsr is triggered. 
  Buffer having the data read from codec will be indicated by
  the index 'activeInBuf'
  
  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Connect linein audio cable from PC to pink Jack on DSP shield.
  4. Connect head phone to green jack of DSP shield.
  5. Open Serial Monitor and connect to the Arduino Uno COM port.
  6. Set the baud rate to 9600.
  7. Observe the messages displayed on the Serial Monitor.
  8. Play audio in PC and listen to the audio from head phone.
*/

#include "Audio.h"

interrupt void dmaIsr(void)
{
      AudioC.isrDma();
}

void setup() 
{
        int status;

	Serial.print("\n Audio TEST!\n");

        status = AudioC.Audio();
        if(status != 0)
        {
            Serial.print("\n Audio Init failed!\n");
        }
        else
        {
            Serial.print("\n Audio Init Done!\n");
        }

        AudioC.attachIntr((INTERRUPT_IsrPtr)dmaIsr);

        Serial.print("\n Audio module Started !\n");      
}

void loop() {
}
