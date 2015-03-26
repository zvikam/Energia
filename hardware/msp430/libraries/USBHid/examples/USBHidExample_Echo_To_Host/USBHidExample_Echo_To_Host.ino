/*
  USB HID
 
 Receives from USB HID and Echoes back the data
 
 modified February 26th, 2015
 by Arthi Bhat
 based on USBSerial example 
 by Stefan Schauer
 
 To run this example:
    -Download the example to Launchpad
    -Power cycle the Launchpad
	-Bring up HidDemo Tool and connect to USB
	-Type in characters in 'Send And Receive' box
     and press 'Send' button  
 
 */

#include <USBHumanInterface.h>
USBHumanInterface myHID(1);
uint8_t i = 0;

void setup()
{
  digitalWrite(RED_LED, LOW);    // set the LED off
  digitalWrite(GREEN_LED, LOW);  // set the LED off
  pinMode(RED_LED, OUTPUT);      //set direction of red pin to output
  pinMode(GREEN_LED, OUTPUT);   //set direction of green pin to output
  myHID.HID_setup();            //configure USB
  digitalWrite(GREEN_LED, HIGH);  // turn green LED on   
     
}

void loop()
{

    uint16_t user_buffer_size = 130;   
	uint8_t buffer[user_buffer_size];     // User buffer to hold the data sent by the GUI
	uint16_t byte_count = 0;
	
    //transmit and receive USB data only if HID is enumerated
    if(myHID.HID_start())
	{
		//transmit user entered data to HID device
		byte_count = myHID.HID_receiveDataFromHost(buffer, user_buffer_size);
		//receive data from HID device
		myHID.HID_sendDataToHost(buffer, byte_count);
        //Toggle the red LED
		i ^= HIGH;                   // Toggle value
		digitalWrite(RED_LED, i);    // toggle the LED
	}


}