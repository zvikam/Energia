/*
  RTC DSP API example sketch
  
  This demo configures the RTC date and time and reads the 
  updated date and time for every 1 secs. Date and time
  value read from RTC library shall be displayed on
  serial monitor.
  
  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Disconnect and reconnect the USB cable.
  4. Open Serial Monitor and connect to the Arduino Uno COM port.
  5. Set the baud rate to 9600.
  6. Send any character using keyboard.
  6. Observe the messages displayed on the Serial Monitor.
*/

#include "RTC_lib.h"

RTCDate  rtcDateRead;
RTCTime  rtcTimeRead;

void setup() 
{   
    int            result;  
    long           baudRate;
    RTCDate  rtcDate;
    RTCTime  rtcTime;    
    char charVal;
            
    Serial.println("RTC DSP API Example\n");  
    
    Serial.println("Date Format - DD:MM:YY");  
    Serial.println("Time Format - HH:MM:SS");  
    
    RTC.init();	
    
	rtcTime.hours = 10;
	rtcTime.mins  = 10;
	rtcTime.secs  = 0;
	rtcTime.msecs = 0;		
	result = RTC.setTime(&rtcTime);
        if(result != 0)
        {
            Serial.println("RTC time setting failed");
        }
        else
        {
                delay(10);  
        	rtcDate.day   = 23;
        	rtcDate.month = 9;
        	rtcDate.year  = 13;	
        	RTC.setDate(&rtcDate);        
                if(result != 0)
                {
                    Serial.println("RTC date setting failed");
                }
                else        
                {
                    RTC.start();    
                    
                    delay(1000);                
                    RTC.getDate(&rtcDateRead);
                
                    Serial.print ("\nCurrent Date - ");
                    Serial.print ((long)rtcDateRead.day);	
                    Serial.print (":");	
                    Serial.print ((long)rtcDateRead.month);	
                    Serial.print (":");	
                    Serial.println ((long)rtcDateRead.year);	                
                }               
        }
}

void loop() 
{ 	
	RTC.getTime(&rtcTimeRead);	       
 	
        Serial.print ("\nCurrent Time - ");
        Serial.print ((long)rtcTimeRead.hours);	
        Serial.print (":");	
        Serial.print ((long)rtcTimeRead.mins);	
        Serial.print (":");	
        Serial.print ((long)rtcTimeRead.secs);	                                    
        
        delay(1000);
}