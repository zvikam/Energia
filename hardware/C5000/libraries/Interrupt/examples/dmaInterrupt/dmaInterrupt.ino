/*
  Interrupt Example for DMA
  Configures all the DMA channels for data transfer, in interrupt mode.
  DMA is configured with proper source and destination address and data length.
  Data in the source buffer is copied into the destination buffer, using DMA.
  The read and write buffer contents should match with each other.

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the messages displayed on the Serial Monitor.
  6. The read and write buffer contents should match with each other for all
     the supported DMA channels.
*/

#define DMA_BUFFER_SIZE    (512u)

volatile int interrupt_occurred = 0;

unsigned short *dmaSRCBuff = NULL;
unsigned short *dmaDESTBuff = NULL;

interrupt void dma_isr(void)
{
    unsigned int ifrValue;

    ifrValue = DMA.getInterruptStatus();
    DMA.clearInterruptStatus(ifrValue);

    interrupt_occurred = 1;
}

void setup()
{
    DMAConfig      dmaConfig;
    int            status;
    unsigned short chanNumber;
    unsigned short index;
    volatile int   delay;

    Serial.println("\r\nDMA INTERRUPT MODE TEST!");

    /* Create DMA data buffers and initialize config buffer */	
    status = DMA.dmaInit(&dmaConfig, DMA_BUFFER_SIZE);
    if (status != 0)
    {
        Serial.print("DMA_init() Failed \n");
        return;
    }

    dmaSRCBuff  = dmaConfig.srcAddr;
    dmaDESTBuff = dmaConfig.destAddr;

    dmaConfig.enableDmaInt = 1;

    for (index = 0; index < DMA_BUFFER_SIZE; index++)
    {
        dmaSRCBuff[index]  = index;
        dmaDESTBuff[index] = 0x0000;
    }

    initInterrupt((INTERRUPT_DispatchTable *)0x0000);
    attachInterrupt(INTERRUPT_DMA, (INTERRUPT_IsrPtr)dma_isr, 0);

    /* Enabling Interrupt */
    enableInterrupt(INTERRUPT_DMA);

    status = DMA.init();
    if (status != 0)
    {
        Serial.println("DMA_init() Failed");
    }

    for ( chanNumber = 0; chanNumber < DMA_CHANNEL_MAX; chanNumber++)
    {
        interrupt_occurred = 0;

        Serial.print("Test for DMA Channel No : ");
        Serial.println((long)chanNumber);

        status = DMA.openChannel(chanNumber);
        if (status != 0)
        {
            Serial.println("DMA_open() Failed");
            break;
        }

        status = DMA.configChannel(chanNumber, dmaConfig);
        if (status != 0)
        {
            Serial.println("DMA_config() Failed");
            break;
        }

        status = DMA.start(chanNumber);
        if (status != 0)
        {
            Serial.println("DMA_start() Failed");
            break;
        }

        while (1)
        {
            for (delay = 0; delay < 1000; delay++) ;

            if (1 == interrupt_occurred)
            {
                break;
            }
        }

        status = DMA.closeChannel(chanNumber);
        if (status != 0)
        {
            Serial.println("DMA.close() Failed");
            break;
        }

        for (index = 0; index < DMA_BUFFER_SIZE; index++)
        {
            if (dmaSRCBuff[index] != dmaDESTBuff[index])
            {
                Serial.print("Buffer miss matched at position ");
                Serial.println((long)index);
                break;
            }
        }

        if (index == DMA_BUFFER_SIZE)
        {
            Serial.print("DMA Transfer for Channel No: ");
            Serial.print((long)chanNumber);
            Serial.println(" Successful");
            Serial.println("Source and Destination Buffers Match!!");
            Serial.println(" ");
        }

        for (index = 0; index < DMA_BUFFER_SIZE; index++)
        {
            dmaSRCBuff[index]  = index;
            dmaDESTBuff[index] = 0x0000;
        }
    }

    if (chanNumber == 16)
    {
        Serial.println("\r\nDMA INTERRUPT MODE TEST PASSED!!");
        xfOn();
    }
    else
    {
        Serial.println("\r\n DMA INTERRUPT MODE TEST FAILED!!");
        xfOff();
    }

	/* Delete the buffers */
	DMA.dmaDeInit(&dmaConfig);
}

void loop()
{
}
