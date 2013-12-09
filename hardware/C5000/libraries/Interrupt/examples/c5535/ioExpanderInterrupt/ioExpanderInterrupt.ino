/*
  IO expander Interrupt Example

  Configures interrupt for IO expander and waits for the interrupt
  on IO expander pins. Interrupt on IO expander can be generated
  by changing the DIP switch states on SW1.

  Note: This demo is specific for C5535 DSP shield.
  May not work/compile for other platforms

  Procedure:
  1. Connect Arduino to host PC using USB cable.
  2. Verify and Upload the example binary to DSP shield.
  3. Open Serial Monitor and connect to the Arduino Uno COM port.
  4. Set the baud rate to 9600.
  5. Observe the messages displayed on the Serial Monitor.
  6. Change any DIP switch state on SW1 to generate interrupt
*/

volatile int intr_flag = 0;

interrupt void INT1_isr(void)
{
  CSL_CPU_REGS->IFR0 = CSL_CPU_REGS->IFR0;
  disableInterrupt(INTERRUPT_INT1);
  intr_flag = 1;
}

unsigned int cmd[2];
unsigned int readBuf[2];
int status;
unsigned int bytesAvail;
unsigned int pinNum;
unsigned int pinVal;

void setup()
{
    Serial.print("IO Expander Interrupt test demo!\n\n");

    pinMode(E3, OUTPUT);
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
    pinMode(E0, OUTPUT);

    /* Configure input pins */
    for(pinNum = IO0; pinNum <= IO9; pinNum++)
    {
        pinMode(pinNum, INPUT);
    }

    pinMode(SW1, INPUT);
    pinMode(SW2, INPUT);
    pinMode(SW3, INPUT);
    pinMode(SW4, INPUT);

    initInterrupt((INTERRUPT_DispatchTable *)0x0000);

    Serial.print("Enabling INT1 Interrupt\n");
    attachInterrupt(INTERRUPT_INT1, (INTERRUPT_IsrPtr)INT1_isr, 0);
    // Enabling Interrupt
    enableInterrupt(INTERRUPT_INT1);

    Serial.print("Change any DIP switch state on SW1 to generate interrupt!\n");
}

void loop()
{
      if(intr_flag == 1)
        {
          Serial.print("\nINT1 Interrupt is triggered!!\n");
          Serial.print("INT1 Interrupt is disabled\n\n");
          intr_flag = 0;

	  /* Read all the input pin values */
	  for(pinNum = IO0; pinNum <= IO9; pinNum++)
	  {
	  	pinVal = digitalRead(pinNum);
	  }

	  pinVal = digitalRead(SW1);
	  pinVal = digitalRead(SW2);
	  pinVal = digitalRead(SW3);
	  pinVal = digitalRead(SW4);

          Serial.print("All the IO Expander Input pins are read\n");
          Serial.print("Enabling interrupt Again!\n");
          Serial.print("Change any DIP switch state on SW1 to generate interrupt!\n");
          delay(1000);
          enableInterrupt(INTERRUPT_INT1);
       }
}