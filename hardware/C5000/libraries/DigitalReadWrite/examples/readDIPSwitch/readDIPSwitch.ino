/*
  DIP switch read demo
  
  This program reads the DIP switch states on SW1 on displays on 
  serial monitor

  Note: This demo is specific for C5535 DSP shield. 
  May not work/compile for other platforms

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the messages displayed on the Serial Monitor.  
  6. Run the demo by changing the DIP switch states
*/

unsigned int pinVal;   

void setup()
{   
    Serial.print("C5535 DSP Shield DIP Switch Read Demo\n\n");          
    
    pinVal = digitalRead(SW1);                
    if(pinVal)
    {
    	Serial.print("DIP Switch SW1 is ON\n");          
    }
    else
    {
    	Serial.print("DIP Switch SW1 is OFF\n");          
    }
    
    pinVal = digitalRead(SW2);                
    if(pinVal)
    {
    	Serial.print("DIP Switch SW2 is ON\n");          
    }
    else
    {
    	Serial.print("DIP Switch SW2 is OFF\n");          
    }    
    
    pinVal = digitalRead(SW3);                
    if(pinVal)
    {
    	Serial.print("DIP Switch SW3 is ON\n");          
    }
    else
    {
    	Serial.print("DIP Switch SW3 is OFF\n");          
    }    
    
    pinVal = digitalRead(SW4);                
    if(pinVal)
    {
    	Serial.print("DIP Switch SW4 is ON\n");          
    }
    else
    {
    	Serial.print("DIP Switch SW4 is OFF\n");          
    }      
}

void loop()
{

}