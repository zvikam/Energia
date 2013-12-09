/*
  Direct Memory Access
  Configures all the DMA channels for data transfer.
  Data in the source buffer is copied into the destination buffer.
  DMA is configured with proper source and destination address and data length.
  Configured values are read back and are verified with the original values.

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the messages displayed on the Serial Monitor.
  6. Read and write buffer contents should match with each other for all
     the supported DMA channels.
*/

#define DMA_BUFFER_SIZE    (512u)

unsigned short *dmaSRCBuff;
unsigned short *dmaDESTBuff;

void setup()
{
    DMAConfig      dmaConfig;
    int            status;
    unsigned short chanNumber;
    unsigned short index;

    dmaSRCBuff  = NULL;
    dmaDESTBuff = NULL;

    Serial.print("\n DMA POLLED MODE TEST!\n");

    /* Create DMA data buffers and initialize config buffer */	
    status = DMA.dmaInit(&dmaConfig, DMA_BUFFER_SIZE);
    if (status != 0)
    {
        Serial.print("DMA_init() Failed \n");
    }

    dmaSRCBuff  = dmaConfig.srcAddr;
    dmaDESTBuff = dmaConfig.destAddr;

    // initialize DMA.
    status = DMA.init();
    if (status != 0)
    {
        Serial.print("DMA_init() Failed \n");
        return;
    }

    for(chanNumber = 0; chanNumber < DMA_CHANNEL_MAX; chanNumber++)
    {
        for(index = 0; index < DMA_BUFFER_SIZE; index++)
        {
            dmaSRCBuff[index]  = index;
            dmaDESTBuff[index] = 0x0000;
        }

        Serial.print("\n Test for DMA Channel No :\t");
        Serial.print((long)chanNumber);

        status = DMA.openChannel(chanNumber);
        if (status != 0)
        {
            Serial.print("DMA_open() Failed \n");
            break;
        }

        status = DMA.configChannel(chanNumber, dmaConfig);
        if (status != 0)
        {
            Serial.print("DMA_config() Failed \n");
            break;
        }

        status = DMA.start(chanNumber);
        if (status != 0)
        {
            Serial.print("DMA_start() Failed \n");
            break;
        }

        while(DMA.getStatus(chanNumber));

        status = DMA.closeChannel(chanNumber);
        if (status != 0)
        {
            Serial.print("DMA.closeChannel() Failed \n");
            break;
        }

        for(index = 0; index < DMA_BUFFER_SIZE; index++)
        {
            if(dmaSRCBuff[index] != dmaDESTBuff[index])
            {
                Serial.print("Buffer miss matched at position");
                Serial.print((long)index);
                break;
            }
        }

        if(index == DMA_BUFFER_SIZE)
        {
            Serial.print(" Success");
        }
    }

    if(chanNumber == 16)
    {
        Serial.print("\n\n DMA POLLED MODE TEST PASSED!!\n");
    }
    else
    {
        Serial.print("\n\n DMA POLLED MODE TEST FAILED!!\n");
    }

    DMA.dmaDeInit(&dmaConfig);
}

void loop()
{

}
