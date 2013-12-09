/*
  This test verifies whether the GPT2 is decrementing the counter or not.
  GPT2 is configured with a count value of 0x20000 and pre-scaler divider
  value of 2. GPT2 is started and counter value is read. After few
  cycles of delay GPT2 counter value is read again. Both the counter values
  are compared to verify whether the second count value is less
  than the first counter value or not and the test passes if it is true.
  
  This sketch dmonstrates usage of function Timer.initialize

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the output on Serial Monitor
*/

#include <Timers.h>

void setup() {
	int     	          status;
	unsigned long             timeCnt1;
	unsigned long             timeCnt2;
	volatile unsigned short   delay;

	status = 0;
	
	Serial.print("\nGPT - Example for initialize() \n");

	/* Open the GPT module for GPT 1 instance */
	status = Timer.selectTimer(GPT1);
	if(0 != status)
	{
 	    Serial.print("GPT Open Failed\n");
	}
	else
	{
	    Serial.print("GPT Open Successful\n");
	}

	/* Configure GPT period */
	Timer.initialize((long)0x20000);

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
	    Serial.print("GTP Time Count Compare Failed\n");
	}
	else
	{
	    Serial.print("GTP Time Count Compare Successful\n");
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

