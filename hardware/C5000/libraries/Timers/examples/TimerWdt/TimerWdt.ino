/*
  This test verifies Watch Dog Timer

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the output on Serial Monitor
*/

#include <Timers.h>

void setup() {
	int              status;
	WDT_Config	 hwConfig;
	unsigned long    counter;
	unsigned long    time;
	unsigned short	 delay;

	hwConfig.counter  = 0xFFFF;
	hwConfig.prescale = 0x00FF;

	Serial.print("Watchdog Timer Example\r\n");

	/* Open the WDTIM module */
	status = Timer.setWdt(0, hwConfig);
	if(status != 0)
	{
		Serial.print("WDTIM: Set watchdog timer Failed\r\n");
	}
	else
	{
		Serial.print("WDTIM: Set watchdog timer Passed\r\n");
	}

	/* Start the watch dog timer */
	status = Timer.startWdt();
	if(0 != status)
	{
		Serial.print("WDTIM: Start for the watchdog Failed\r\n");
	}
	else
	{
		Serial.print("WDTIM: Start for the watchdog Passed\r\n");
	}

	for (delay = 0; delay < 10; delay++);

	/* Stop the watch dog timer */
	status = Timer.stopWdt();
	if(0 != status)
	{
		Serial.print("WDTIM: Stop for the watchdog Failed\r\n");
	}
	else
	{
		Serial.print("WDTIM: Stop for the watchdog Passed\r\n");
	}

	/* Start the watch dog timer */
	status = Timer.startWdt();
	if(0 != status)
	{
		Serial.print("WDTIM: Start for the watchdog Failed\r\n");
	}
	else
	{
		Serial.print("WDTIM: Start for the watchdog Passed\r\n");
	}

	counter = 0;
	for(counter=0; counter<0x105; counter++)
	{
		if(counter < 0x100)
		{
			Timer.serviceWdt();
			Serial.print("\r\nWDT Service - ");
			Serial.println((long)counter);
		}
		else
		{
			Serial.print("\r\nWDT Out of Service - ");
			Serial.println((long)counter);
		}

		counter++;
	}
	
        Serial.print("End of Watchdog Timer Example\r\n");
}

void loop() {
}

