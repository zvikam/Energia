/*
 * FIR Filter demo:
 * Reads data from codec audio IN, sends the data to FIR filter and 
 * finally sends the filtered audio to the codec OUT which can be 
 * listened on headphone.
 *
 * Filter is configured as a Low Pass Filter(LPF) with cut-off 
 * frequency as 2kHz.
 */

#include "Audio.h"
#include "filter.h"
#include "OLED.h"

// Buffer to hold the Input Samples of left channel, for the FIR filter 
int filterIn1[I2S_DMA_BUF_LEN];

// Buffer to hold the Input Samples of right channel, for the FIR filter 
int filterIn2[I2S_DMA_BUF_LEN];

// Buffer to hold the Output Samples of left channel, from the FIR filter
int filterOut1[I2S_DMA_BUF_LEN];

// Buffer to hold the Output Samples of right channel, from the FIR filter
int filterOut2[I2S_DMA_BUF_LEN];

// Variable to indicate to the FIR Filtering section that the Input samples
// are ready to be filtered
unsigned short readyForFilter = 0;

// Variable to indicate that the FIR filtering is completed and the filtered
//  samples are available in the "filterOut" buffer
unsigned short filterBufAvailable = 0;

// Variable to switch between the data buffers of the Audio library
unsigned short writeBufIndex = 0;

// Length of the Coefficient Vector
#define FILTER_LENGTH (202)

// Filter coefficients with 200 taps
int coeffs[FILTER_LENGTH] = {
        7,      6,      4,      2,      0,     -2,     -5,     -7,     -9,
      -11,    -12,    -12,    -12,    -10,     -8,     -4,      0,      5,
       10,     15,     19,     23,     25,     26,     24,     21,     16,
        9,      0,    -10,    -20,    -30,    -39,    -46,    -50,    -51,
      -49,    -42,    -31,    -17,      0,     19,     38,     57,     73,
       86,     93,     94,     89,     76,     56,     31,      0,    -34,
      -68,   -100,   -129,   -150,   -163,   -164,   -154,   -132,    -97,
      -53,      0,     58,    117,    173,    222,    260,    282,    286,
      269,    231,    172,     94,      0,   -104,   -212,   -318,   -412,
     -488,   -538,   -555,   -533,   -467,   -356,   -200,      0,    239,
      510,    805,   1114,   1424,   1725,   2005,   2252,   2455,   2607,
     2701,   2733,   2701,   2607,   2455,   2252,   2005,   1725,   1424,
     1114,    805,    510,    239,      0,   -200,   -356,   -467,   -533,
     -555,   -538,   -488,   -412,   -318,   -212,   -104,      0,     94,
      172,    231,    269,    286,    282,    260,    222,    173,    117,
       58,      0,    -53,    -97,   -132,   -154,   -164,   -163,   -150,
     -129,   -100,    -68,    -34,      0,     31,     56,     76,     89,
       94,     93,     86,     73,     57,     38,     19,      0,    -17,
      -31,    -42,    -49,    -51,    -50,    -46,    -39,    -30,    -20,
      -10,      0,      9,     16,     21,     24,     26,     25,     23,
       19,     15,     10,      5,      0,     -4,     -8,    -10,    -12,
      -12,    -12,    -11,     -9,     -7,     -5,     -2,      0,      2,
        4,      6,      7,      0
};

// Delay buffer used by the FIR filtering algorithm for Left Channel
int delayBufferL[FILTER_LENGTH + 2];

// Delay buffer used by the FIR filtering algorithm for Right Channel
int delayBufferR[FILTER_LENGTH + 2];

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
        copyShortBuf(AudioC.audioInLeft[AudioC.activeInBuf],
                     filterIn1, I2S_DMA_BUF_LEN);
        copyShortBuf(AudioC.audioInRight[AudioC.activeInBuf],
                     filterIn2, I2S_DMA_BUF_LEN);
        readyForFilter = 1;
    }
    else if ((ifrValue >> DMA_CHAN_WriteR) & 0x01)
    {
        if (filterBufAvailable)
        {
            /* Filtered buffers need to be copied to audio out buffers as
               audio library is configured for non-loopback mode */
            writeBufIndex = (AudioC.activeOutBuf == FALSE)? TRUE: FALSE;
            copyShortBuf(filterOut1, AudioC.audioOutLeft[writeBufIndex],
                         I2S_DMA_BUF_LEN);
            copyShortBuf(filterOut2, AudioC.audioOutRight[writeBufIndex],
                         I2S_DMA_BUF_LEN);
            filterBufAvailable = 0;
        }
    }

    /* Calling AudioC.isrDma() will copy the buffers to Audio Out of the Codec,
     * initiates next DMA transfers of Audio samples to and from the Codec
     */
    AudioC.isrDma();

    // Check if filter buffers are ready. No filtering required for write interrupt
    if (readyForFilter)
    {
        readyForFilter = 0;

        // Filter Left Audio Channel
        filter_fir(filterIn1, coeffs, filterOut1, delayBufferL,
                   I2S_DMA_BUF_LEN, FILTER_LENGTH);
        // Filter Right Audio Channel
        filter_fir(filterIn2, coeffs, filterOut2, delayBufferR,
                   I2S_DMA_BUF_LEN, FILTER_LENGTH);

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
    fillShortBuf(filterIn1, 0, I2S_DMA_BUF_LEN);    
    fillShortBuf(filterIn2, 0, I2S_DMA_BUF_LEN);
    fillShortBuf(filterOut1, 0, I2S_DMA_BUF_LEN);
    fillShortBuf(filterOut2, 0, I2S_DMA_BUF_LEN);

    /* Clear the delay buffers, which will be used by the FIR filtering
       algorithm, These buffers need to be initialized to all zeroes in the
       beginning of the FIR filtering algorithm */
    fillShortBuf(delayBufferL, 0, (FILTER_LENGTH + 2));       
    fillShortBuf(delayBufferR, 0, (FILTER_LENGTH + 2));       
    
    /* Audio library is configured for non-loopback mode. Gives enough time for
       FIR filter processing in ISR */
    status = AudioC.Audio(TRUE);
    if (status == 0)
    {
        disp.print("FIR Filter ON");
        AudioC.attachIntr(dmaIsr);
    }        
}

void loop()
{
}
