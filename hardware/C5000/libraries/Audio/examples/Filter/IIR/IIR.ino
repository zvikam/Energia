/*
  IIR Filter demo. This demo reads data from codec audio IN, sends the data 
  to IIR filter and finally sends the filtered \audio to the codec OUT 
  which can be listened on headphone.

  This example acts as a 8th order Low Pass Filter(LPF) 
  with cut-off frequency as 5kHz.

*/

#include "FFT.h"
#include "Audio.h"
#include "filter.h"
#include "OLED.h"
#include "SD.h"

/** Buffer to hold the Input Samples of left channel, for the IIR filter */
#pragma DATA_ALIGN(32);
int filterInLeft[I2S_DMA_BUF_LEN];
/** Buffer to hold the Input Samples of right channel, for the IIR filter */
#pragma DATA_ALIGN(32);
int filterInRight[I2S_DMA_BUF_LEN];

/** Buffer to hold the Output Samples of left channel, from the IIR filter */
#pragma DATA_ALIGN(32);
int filterOutLeft[I2S_DMA_BUF_LEN];
/** Buffer to hold the Output Samples of right channel, from the IIR filter */
#pragma DATA_ALIGN(32);
int filterOutRight[I2S_DMA_BUF_LEN];

/** Variable to indicate to the IIR Filtering section that the Input samples
    are ready to be filtered */
unsigned short readyForFilter = 0;

/** Variable to indicate that the IIR filtering is completed and the filtered
    samples are available in the "filterOut" buffer */
unsigned short filterBufAvailable = 0;

/** Variable to switch between the data buffers of the Audio library */
unsigned short writeBufIndex = 0;

/** Length of the Coefficient Vector, used by the IIR filter */
#define FILTER_LENGTH (24)

#pragma DATA_ALIGN(32);
int coeffs[FILTER_LENGTH] = {
//8th order, 5k cutoff LPF, assumes 48k sample frequency.
15,-8139,2067,8192,16389,8194,
15,-8630,2686,8192,16589,8400,
15,-9713,4051,8192,16379,8190,
15,-11618,6453,8192,16179,7990
};

#define IIR_ORDER_MAX    (16)
#define DELAY_COUNT      (4)
#define DELAY_BUF_SIZE   ((IIR_ORDER_MAX/2)*(DELAY_COUNT))

/** Delay buffer used by the IIR filter for Left Channel */
#pragma DATA_ALIGN(32);
int delayBufferL[DELAY_BUF_SIZE];
/** Delay buffer used by the IIR filter for Right Channel */
#pragma DATA_ALIGN(32);
int delayBufferR[DELAY_BUF_SIZE];

/**
 *   API to copy contents of one buffer to an another buffer
 */
void copyBuf16(int *input, int *output, unsigned short dataLength)
{
    unsigned short index;

    for (index = 0; index < dataLength; index++)
    {
        output[index] = input[index];
    }
}

/**
 *   DMA Interrupt Service Routine
 */
interrupt void dmaIsr(void)
{
    unsigned short ifrValue;

    ifrValue = DMA.getInterruptStatus();
    if ((ifrValue >> DMA_CHAN_ReadR) & 0x01)
    {
        /* Data read from codec is copied to filter input buffers.
           Filtering is done after configuring DMA for next block of transfer
           ensuring no data loss */
        copyBuf16((int *)AudioC.audioInLeft[AudioC.activeInBuf], filterInLeft,
                  I2S_DMA_BUF_LEN);
        copyBuf16((int *)AudioC.audioInRight[AudioC.activeInBuf], filterInRight,
                  I2S_DMA_BUF_LEN);
        readyForFilter = 1;
    }
    else if ((ifrValue >> DMA_CHAN_WriteR) & 0x01)
    {
        if (filterBufAvailable)
        {
            /* Filtered buffers need to be copied to audio out buffers as audio
               library is configured for non-loopback mode */
            writeBufIndex = (AudioC.activeOutBuf == FALSE)? TRUE: FALSE;
            copyBuf16(filterOutLeft, (int *)AudioC.audioOutLeft[writeBufIndex],
                      I2S_DMA_BUF_LEN);
            copyBuf16(filterOutRight, (int *)AudioC.audioOutRight[writeBufIndex],
                      I2S_DMA_BUF_LEN);
            filterBufAvailable = 0;
        }
    }

    AudioC.isrDma();

    if (readyForFilter)
    {
        readyForFilter = 0;

        filter_iirArbitraryOrder(I2S_DMA_BUF_LEN, filterInLeft, filterOutLeft, coeffs, delayBufferL, 8);
        filter_iirArbitraryOrder(I2S_DMA_BUF_LEN, filterInRight, filterOutRight, coeffs, delayBufferR, 8);        

        filterBufAvailable = 1;
    }
}

void setup()
{
    int status;
    int index;

    pinMode(LED0, OUTPUT);
    digitalWrite(LED0, HIGH);

    disp.oledInit();
    disp.clear();
    disp.setline(0);
    disp.flip();
    disp.print("IIR Filter");
    disp.setline(1);

    /* Clear all the data buffers */
    for (index = 0; index < I2S_DMA_BUF_LEN; index++)
    {
        filterInLeft[index]   = 0;
        filterInRight[index]  = 0;
        filterOutLeft[index]  = 0;
        filterOutRight[index] = 0;
    }
    
    for (index = 0; index < DELAY_BUF_SIZE; index++)
    {    
    	delayBufferL[index] = 0;
    	delayBufferR[index] = 0;
    }

    /* Audio library is configured for non-loopback mode. Gives enough time for
       processing in ISR */
    status = AudioC.Audio(TRUE);
    if (status != 0)
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

void loop()
{
}
