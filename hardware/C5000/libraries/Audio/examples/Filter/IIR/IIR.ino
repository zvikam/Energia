/*
 * IIR Filter demo:
 * This demo reads data from codec audio IN, sends the data
 * to IIR filter and finally sends the filtered audio to the codec OUT
 * which can be listened on headphone.
 *
 * This program acts as a 8th order Low Pass Filter(LPF)
 * with cut-off frequency as 5kHz.
 *
 */

#include "Audio.h"
#include "filter.h"
#include "OLED.h"

#define IIR_ORDER_MAX    (16)
#define DELAY_COUNT      (4)
#define DELAY_BUF_SIZE   ((IIR_ORDER_MAX/2)*(DELAY_COUNT))

// Length of the Coefficient Vector, used by the IIR filter
#define FILTER_LENGTH (24)

/* Variable to indicate to the IIR Filtering section that the Input samples
   are ready to be filtered */
unsigned short readyForFilter = 0;

/* Variable to indicate that the IIR filtering is completed and the filtered
   samples are available in the "filterOut" buffer */
unsigned short filterBufAvailable = 0;

// Variable to switch between the data buffers of the Audio library
unsigned short writeBufIndex = 0;

// Buffer to hold the Input Samples of left channel, for the IIR filter
#pragma DATA_ALIGN(32);
int filterInLeft[I2S_DMA_BUF_LEN];

// Buffer to hold the Input Samples of right channel, for the IIR filter
#pragma DATA_ALIGN(32);
int filterInRight[I2S_DMA_BUF_LEN];

// Buffer to hold the Output Samples of left channel, from the IIR filter
#pragma DATA_ALIGN(32);
int filterOutLeft[I2S_DMA_BUF_LEN];

// Buffer to hold the Output Samples of right channel, from the IIR filter
#pragma DATA_ALIGN(32);
int filterOutRight[I2S_DMA_BUF_LEN];

// Filter coefficients - 8th order, 5k cutoff LPF, assumes 48k sample frequency
#pragma DATA_ALIGN(32);
int coeffs[FILTER_LENGTH] = {    
    15, -8139, 2067, 8192, 16389, 8194,
    15, -8630, 2686, 8192, 16589, 8400,
    15, -9713, 4051, 8192, 16379, 8190,
    15, -11618, 6453, 8192, 16179, 7990
};

// Delay buffer used by the IIR filtering algorithm for Left Channel
#pragma DATA_ALIGN(32);
int delayBufferL[DELAY_BUF_SIZE];

// Delay buffer used by the IIR filtering algorithm for Right Channel
#pragma DATA_ALIGN(32);
int delayBufferR[DELAY_BUF_SIZE];

// DMA Interrupt Service Routine
interrupt void dmaIsr(void)
{
    unsigned short ifrValue;

    ifrValue = DMA.getInterruptStatus();
    if ((ifrValue >> DMA_CHAN_ReadR) & 0x01)
    {
        /* Data read from codec is copied to filter input buffers.
           Filtering is done after configuring DMA for next block of transfer
           ensuring no data loss */
        copyShortBuf(AudioC.audioInLeft[AudioC.activeInBuf], filterInLeft,
                     I2S_DMA_BUF_LEN);
        copyShortBuf(AudioC.audioInRight[AudioC.activeInBuf], filterInRight,
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
            copyShortBuf(filterOutLeft, AudioC.audioOutLeft[writeBufIndex],
                         I2S_DMA_BUF_LEN);
            copyShortBuf(filterOutRight, AudioC.audioOutRight[writeBufIndex],
                         I2S_DMA_BUF_LEN);
            filterBufAvailable = 0;
        }
    }

    /* Calling AudioC.isrDma() will copy the buffers to Audio Out of the Codec,
     * initiates next DMA transfers of Audio samples to and from the Codec
     */
    AudioC.isrDma();

    if (readyForFilter)
    {
        readyForFilter = 0;

        // Filter Left Audio Channel - configuring filter for 8th order
        filter_iirArbitraryOrder(I2S_DMA_BUF_LEN, filterInLeft, filterOutLeft, coeffs, delayBufferL, 8);

        // Filter Right Audio Channel - configuring filter for 8th order
        filter_iirArbitraryOrder(I2S_DMA_BUF_LEN, filterInRight, filterOutRight, coeffs, delayBufferR, 8);

        filterBufAvailable = 1;
    }
}

// Initializes OLED and Audio modules
void setup()
{
    int status;
    int index;

    pinMode(LED0, OUTPUT);
    digitalWrite(LED0, HIGH);

    //Initialize OLED module for status display
    disp.oledInit();
    disp.clear();    
    disp.flip();    
    disp.setline(1);

    // Clear all the data buffers
    fillShortBuf(filterInLeft, 0, I2S_DMA_BUF_LEN);        
    fillShortBuf(filterInRight, 0, I2S_DMA_BUF_LEN);    
    fillShortBuf(filterOutLeft, 0, I2S_DMA_BUF_LEN);    
    fillShortBuf(filterOutRight, 0, I2S_DMA_BUF_LEN);    
    
    /* Clear the delay buffers, which will be used by the IIR filtering
       algorithm, These buffers need to be initialized to all zeroes in the
       beginning of the IIR filtering algorithm */
    fillShortBuf(delayBufferL, 0, DELAY_BUF_SIZE);       
    fillShortBuf(delayBufferR, 0, DELAY_BUF_SIZE);       

    /* Audio library is configured for non-loopback mode. Gives enough time for
       processing in ISR */
    status = AudioC.Audio(TRUE);
    if (status == 0)
    {
    	disp.print("IIR Filter ON");
        AudioC.attachIntr(dmaIsr);
    }
}

void loop()
{
}
