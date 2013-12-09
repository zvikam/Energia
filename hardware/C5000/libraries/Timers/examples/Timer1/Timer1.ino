/*
  This test verifies whether the GPT1 is decrementing the counter or not.
  GPT is configured with a count value of 0xFFFF and pre-scaler divider
  value of 256. GPT1 is started and counter value is read. After few
  cycles of delay GPT1 counter value is read again. Both the counter values
  are compared to verify whether the second count value is less
  than the first counter value or not and the test passes if it is true.
  
  This sketch dmonstrates usage of function Timer.configTimer

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the output on Serial Monitor
*/

#include <Timers.h>

void setup() {
	int     	       status;
	GPT_Config 	       hwConfig;
	unsigned long          timeCnt1;
	unsigned long          timeCnt2;
	volatile unsigned short	   delay;

	status = 0;
	
	Serial.print("\nGPT - Example for configTimer() \n");

	/* Open the GPT module for GPT 0 instance */
	status = Timer.selectTimer(GPT0);
	if(0 != status)
	{
	    Serial.print("GPT Open Failed\n");
	}
	else
	{
	    Serial.print("GPT Open Successful\n");
	}

	/* Configure GPT module */
	hwConfig.autoLoad 	 = TRUE;
	hwConfig.ctrlTim 	 = TRUE;
	hwConfig.preScaleDiv     = GPT_PRE_SC_DIV_7;
	hwConfig.prdLow 	 = 0xFFFF;
	hwConfig.prdHigh 	 = 0x0000;

	status =  Timer.configTimer(hwConfig);
	if(0 != status)
	{
	    Serial.print("GPT Config Failed\n");
	}
	else
	{
	    Serial.print("GPT Config Successful\n");
	}

	/* Start the Timer */
	Timer.start();

	/* Read the Timer Count */
	timeCnt1 = Timer.read();

	/* Give Some Delay */
	for(delay = 0; delay < 100; delay++);

	/* Read the Timer Count Again */
	timeCnt2 = Timer.read();

	/* Compare the timer count to verify whether the timer is counting or not */
	if(timeCnt2 >= timeCnt1)
	{
     	    Serial.print("GPT Time Count Compare Failed\n");
	}
	else
	{
    	    Serial.print("GPT Time Count Compare Successful\n");
	}

	/* Stop The Timer */
	Timer.stop();

	/* Close the GPT module */
	status = Timer.close();
	if(0 != status)
	{
    	    Serial.print("GPT Close Failed\n");
	}
	else
	{
 	    Serial.print("GPT Close Successful\n");
	}
	
	Serial.print("\nEnd of Example!\n");
}

void loop() {
}
