/*
  Analog Read
  Reads analog pin data from A0 pin, processes it using FFT and finally
  displays the buffer on the serial console. This example reads the analog pin
  data for every 100 msecs(value in 'TIMER_INTERVAL' macro), the timer interval
  can be increased/decreased by changing the value of this 'TIMER_INTERVAL'
  macro, which is in units of milliseconds.

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the messages displayed on the Serial Monitor.
*/

#include <FFT.h>
#include <Timers.h>
#include <math.h>

/** Timer Interval in msecs */
#define TIMER_INTERVAL   (100)
/** Buffer Size */
#define DATA_BUFFER_SIZE (64)

int dataBufIndex = 0;
int bufferNo = 0;
volatile int bufferFull = 0;

#pragma DATA_ALIGN(32)
int dataBuffer[2][DATA_BUFFER_SIZE];

interrupt void timerIsr();

void setup()
{
    int           status;
    GPT_Config    hwConfig;
    unsigned long cpuClock;
    unsigned long prdValue;

    Serial.println(" ");
    Serial.println("Analog ReadWrite Test!!");

    /* Open the GPT module for GPT 0 instance */
    status = Timer.selectTimer(GPT0);
    if(0 != status)
    {
        Serial.print("GPT Open Failed\n");
        return;
    }

    /* getCpuClock() will return the CPU Clock in kHz */
    cpuClock = getCpuClock();

    /* Divide CPU Clock by the Pre Scale Divider value */
    prdValue = pow(2, GPT_PRE_SC_DIV_1 + 1);

    /* This PRD value will be for 1 msec */
    prdValue = cpuClock / prdValue;

    /* PRD value for the requested Timer Interval */
    prdValue *= TIMER_INTERVAL;

    /* Configure GPT module */
    hwConfig.autoLoad    = TRUE;
    hwConfig.ctrlTim     = TRUE;
    hwConfig.preScaleDiv = GPT_PRE_SC_DIV_1;
    hwConfig.prdLow      = (prdValue & 0xFFFF);
    hwConfig.prdHigh     = ((prdValue >> 16) & 0xFFFF);

    status =  Timer.configTimer(hwConfig);
    if(0 != status)
    {
        Serial.print("GPT Config Failed\n");
        return;
    }

    initInterrupt((INTERRUPT_DispatchTable *)0x0000);
    attachInterrupt(INTERRUPT_TINT, (INTERRUPT_IsrPtr)timerIsr, 0);

    /* Enabling Timer Interrupt */
    enableInterrupt(INTERRUPT_TINT);

    Timer.start();
}

void loop()
{
    int index;

    if (1 == bufferFull)
    {
        FFTransform.FFT(dataBuffer[!bufferNo], DATA_BUFFER_SIZE, DISABLE_SCALE,
                        FFT_REAL, FFTQ15);

        Serial.println("\r\nThe processed data is:");

        for (index = 0; index < DATA_BUFFER_SIZE; index++)
        {
            Serial.println((long)dataBuffer[!bufferNo][index], HEX);
        }

        bufferFull = 0;
    }
}

interrupt void timerIsr()
{
    dataBuffer[bufferNo][dataBufIndex] = analogRead(A0);
    dataBufIndex++;

    if (DATA_BUFFER_SIZE == dataBufIndex)
    {
        bufferNo = !bufferNo;
        bufferFull = 1;
        dataBufIndex = 0;
    }
    Timer.clearInterrupt();
}
