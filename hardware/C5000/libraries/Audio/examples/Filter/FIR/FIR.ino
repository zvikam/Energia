/*
  Example sketch for FIR Filter demo. This demo reads data from
  codec audio IN, sends the data to FIR filter and finally sends the filtered
  audio to the codec OUT which can be listened on headphone.

  This example acts as a Low Pass Filter(LPF) with cut-off frequency as 2kHz.

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

#include "FFT.h"
#include "Audio.h"
#include "filter.h"
#include "OLED.h"

/** Buffer to hold the Input Samples of left channel, for the FIR filter */
int filterIn1[I2S_DMA_BUF_LEN];
/** Buffer to hold the Input Samples of right channel, for the FIR filter */
int filterIn2[I2S_DMA_BUF_LEN];

/** Buffer to hold the Output Samples of left channel, from the FIR filter */
int filterOut1[I2S_DMA_BUF_LEN];
/** Buffer to hold the Output Samples of right channel, from the FIR filter */
int filterOut2[I2S_DMA_BUF_LEN];

/** Variable to indicate to the FIR Filtering section that the Input samples
    are ready to be filtered */
unsigned short readyForFilter = 0;

/** Variable to indicate that the FIR filtering is completed and the filtered
    samples are available in the "filterOut" buffer */
unsigned short filterBufAvailable = 0;

/** Variable to switch between the data buffers of the Audio library */
unsigned short writeBufIndex = 0;

#if 0

/** Length of the Coefficient Vector, used by the FIR filter */
#define FILTER_LENGTH (42)

/** Filter coefficients with 40 taps, used by the FIR filter */
int coeffs[FILTER_LENGTH] = {
     -36,    -46,    -60,    -78,    -95,   -106,   -101,    -69,      0,
     115,    283,    504,    774,   1083,   1416,   1752,   2070,   2347,
    2561,   2697,   2744,   2697,   2561,   2347,   2070,   1752,   1416,
    1083,    774,    504,    283,    115,      0,    -69,   -101,   -106,
     -95,    -78,    -60,    -46,    -36,      0
};

#else

/** Length of the Coefficient Vector, used by the FIR filter */
#define FILTER_LENGTH (202)

/** Filter coefficients with 200 taps, used by the FIR filter */
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
#endif

/** Delay buffer used by the FIR filter for Left Channel */
int delayBufferL[FILTER_LENGTH + 2];
/** Delay buffer used by the FIR filter for Right Channel */
int delayBufferR[FILTER_LENGTH + 2];

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
        copyBuf16((int *)AudioC.audioInLeft[AudioC.activeInBuf],
                  filterIn1, I2S_DMA_BUF_LEN);
        copyBuf16((int *)AudioC.audioInRight[AudioC.activeInBuf],
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
            copyBuf16(filterOut1, (int *)AudioC.audioOutLeft[writeBufIndex],
                      I2S_DMA_BUF_LEN);
            copyBuf16(filterOut2, (int *)AudioC.audioOutRight[writeBufIndex],
                      I2S_DMA_BUF_LEN);
            filterBufAvailable = 0;
        }
    }

    AudioC.isrDma();

    /* This is the FIR Filtering section */
    if (readyForFilter)
    {
        readyForFilter = 0;

        filter_fir(filterIn1, coeffs, filterOut1, delayBufferL,
                   I2S_DMA_BUF_LEN, FILTER_LENGTH);
        filter_fir(filterIn2, coeffs, filterOut2, delayBufferR,
                   I2S_DMA_BUF_LEN, FILTER_LENGTH);

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
    disp.print("FIR Filter ON");
    disp.setline(1);

    /* Clear all the data buffers */
    for (index = 0; index < I2S_DMA_BUF_LEN; index++)
    {
        filterIn1[index] = 0;
        filterIn2[index] = 0;
        filterOut1[index] = 0;
        filterOut2[index] = 0;
    }

    /* Clear the delay buffers */
    for (index = 0; index < (FILTER_LENGTH + 2); index++)
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
