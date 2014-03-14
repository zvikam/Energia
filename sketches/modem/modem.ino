/*
 * modem.pde
 *
 * Copyright (c) 2013 Daniel Berenguer <dberenguer@usapiens.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 11/18/2013
 *
 * Device:
 * Serial gateway or modem
 *
 * Description:
 * This is not a proper SWAP gateway but a simple transparent UART-RF
 * interface. This device can be used from a serial console as hyperterminal
 * or minicom. Wireless packets are passed to/from the host computer in ASCII
 * format whilst configuration is done via AT commands.
 *
 * Visit our wiki for details about the protocol in case you want to develop
 * your own PC library for this device.
 */

#include "panstamp.h"
#include "modem.h"
#include "timer1.h"

/**
 * Hardware version
 */
#define HARDWARE_VERSION        0x00000100

/**
 * Firmware version
 */
#define FIRMWARE_VERSION        0x00000100

/**
 * Manufacturer SWAP ID
 */
#define SWAP_MANUFACT_ID        0x00000001

/**
 * Product SWAP ID
 */
#define SWAP_PRODUCT_ID         0x0000000E

DECLARE_COMMON_CALLBACKS()
DEFINE_COMMON_REGISTERS()
DECLARE_REGISTERS_START()
DECLARE_REGISTERS_END()
DEFINE_COMMON_CALLBACKS()

/**
 * pacKetReceived
 *
 * CCPACKET received
 *
 * @param packet CCPACKET received
 */
void pacKetReceived(CCPACKET *packet)
{
  rxPacket = packet;
  packetAvailable = true;
}

/**
 * isrT1event
 *
 * Timer 1 interrupt routine
 */
void isrT1event(void)
{
  // Halt timer
  timer1.stop();

  // Pending "+++" command?
  if (!strcmp(strSerial, AT_GOTO_CMDMODE))
  {
    // Disable wireless reception interrupt
    MRFI_DISABLE_SYNC_PIN_INT();
    
    enterCommandMode = true;
    serMode = SERMODE_COMMAND;
  }
  memset(strSerial, 0, sizeof(strSerial));
  len = 0;
}

/**
 * handleSerialCmd
 *
 * Handle serial command received
 *
 * 'command'  AT command received
 */
void handleSerialCmd(char* command)
{
  byte i, len;
  byte arrV[2];
  CCPACKET packet;
  ATQUERY atQuery = ATQUERY_REQUEST; 
 
  // Data mode?
  if (serMode == SERMODE_DATA)
  {
    packet.length = strlen(command)/2;
    
    if (packet.length > 0)
    {
      // Convert ASCII string into array of bytes
      for(i=0 ; i<packet.length ; i++)
      {     
        packet.data[i] = charToHex(command[i*2]) << 4;
        packet.data[i] |= charToHex(command[i*2 + 1]);
      }
      // Send packet via RF
      radio.sendData(packet);
    }
  }
  // Command mode?
  else  // serMode = SERMODE_COMMAND
  {
    len = strlen(command);
    
    if (len < 5)
    {
      // Basic attention command
      if (!strcmp(strSerial, AT_ATTENTION))
        Serial.println("OK");
      // Reset modem
      else if (!strcmp(strSerial, AT_RESET))
      {
        Serial.println("OK");
        swReset();
      }
      // Go to serial data mode
      else if (!strcmp(strSerial, AT_GOTO_DATAMODE))
      {
        serMode = SERMODE_DATA;
        Serial.println("OK-Data mode");
        
        // Enable wireless reception interrupt
        MRFI_ENABLE_SYNC_PIN_INT();
      }
    }
    // Set new value
    else 
    {
      if ((strSerial[4] == '=') && (len >= 6))
      {
        // Get new value
        i = (charToHex(strSerial[5]) << 4) & 0xF0;
        i |= charToHex(strSerial[6]) & 0x0F;
        atQuery = ATQUERY_COMMAND;
      }
      // Hardware version
      if (!strncmp(strSerial, AT_HVERSION, 4))
      {
        if (atQuery == ATQUERY_REQUEST)
          Serial.println(HARDWARE_VERSION, HEX);
      }
      // Firmware version
      else if (!strncmp(strSerial, AT_FVERSION, 4))
      {
        if (atQuery == ATQUERY_REQUEST)
          Serial.println(FIRMWARE_VERSION, HEX);
      }
      // Frequency channel
      else if (!strncmp(strSerial, AT_FREQCHANNEL, 4))
      {
        if (atQuery == ATQUERY_COMMAND)
        {
          radio.setChannel(i);
          Serial.println("OK");
        }
        else
          Serial.println(radio.channel, HEX);
      }
      // Synchronization word
      else if (!strncmp(strSerial, AT_SYNCWORD, 4))
      {
        if (atQuery == ATQUERY_COMMAND)
        {
          if ((len-5) == 4)
          {
            arrV[0] = charToHex(strSerial[5]) << 4;
            arrV[0] |= charToHex(strSerial[6]);
            arrV[1] = charToHex(strSerial[7]) << 4;
            arrV[1] |= charToHex(strSerial[8]);
            radio.setSyncWord(arrV);
            Serial.println("OK");
          }
          else
            Serial.println("ERROR");
        }
        else
        {
          Serial.print(radio.syncWord[0], HEX);
          Serial.println(radio.syncWord[1], HEX);
        }
      }
      // Device address
      else if (!strncmp(strSerial, AT_DEVADDRESS, 4))
      {
        if (atQuery == ATQUERY_COMMAND)
        {
          radio.setDevAddress(i);
          Serial.println("OK");
        }
        else
          Serial.println(radio.devAddress, HEX);
      }
      // Address check
      else if (!strncmp(strSerial, AT_ADDRCHECK, 4))
      {
        if (atQuery == ATQUERY_COMMAND)
        {
          if (i == 0)
          {
            radio.disableAddressCheck();
            Serial.println("OK");
          }
          else if (i == 1)
          {
            radio.enableAddressCheck();
            Serial.println("OK");
          }
          else
            Serial.println("ERROR");
        }
        else
          Serial.println("ERROR");
      }
      else
        Serial.println("ERROR");
    }
  }
}

/**
 * setup
 *
 * Arduino setup function
 */
void setup()
{
  Serial.begin(38400);
  Serial.flush();
  Serial.println("");

  // Reset serial buffer
  memset(strSerial, 0, sizeof(strSerial));

  // Setup radio
  panstamp.init();
  digitalWrite(ONBOARD_LED, HIGH);
  
  // Function to be called upon reception of any wireless packet
  panstamp.setPacketRxCallback(pacKetReceived);

  // Default mode is COMMAND 
  Serial.println("Modem ready!");

  // Disable address check from the CC1101 IC
  radio.disableAddressCheck();

  delay(100);

  timer1.attachInterrupt(isrT1event);
  digitalWrite(ONBOARD_LED, LOW);
}

/**
 * loop
 *
 * Arduino main loop
 */
void loop()
{
  if (packetAvailable)
  {
    byte i;
    
    if (rxPacket->length > 5 && serMode == SERMODE_DATA)
    {   
      Serial.print("(");
  
      if (rxPacket->rssi < 0x10)
        Serial.print("0");
      Serial.print(rxPacket->rssi, HEX);
  
      if (rxPacket->lqi < 0x10)
        Serial.print("0");
      Serial.print(rxPacket->lqi, HEX);
      Serial.print(")");
  
      for(i=0 ; i<rxPacket->length ; i++)
      {
        if (rxPacket->data[i] < 0x10)
          Serial.print(0, HEX);    // Leading zero
        Serial.print(rxPacket->data[i], HEX);
      }
  
      Serial.println("");
    }
    packetAvailable = false;
  }
  
  if (enterCommandMode)
  {
    enterCommandMode = false;
    Serial.println("OK-Command mode");
  }
  
  // Read serial command
  if (Serial.available() > 0)
  {
    // Disable wireless reception interrupt
    MRFI_DISABLE_SYNC_PIN_INT();

    ch = Serial.read();

    if (len >= SERIAL_BUF_LEN-1)
    {
      memset(strSerial, 0, sizeof(strSerial));
      len = 0;
    }
    else if (ch == 0x0D) 
    {
      timer1.stop();
      strSerial[len] = 0;
      handleSerialCmd(strSerial);
      memset(strSerial, 0, sizeof(strSerial));
      len = 0;
    }
    else
    {
      strSerial[len] = ch; 
      len++;
      timer1.start(1000);
    }

    // Enable wireless reception interrupt
    MRFI_ENABLE_SYNC_PIN_INT();
  }
}

/**
 * charToHex
 *
 * 'ch' Character to be converted to hexadecimal
 *
 * Returns:
 *  Hex value
 */
byte charToHex(byte ch)
{
  byte val;
  
  if (ch >= 'A' && ch <= 'F')
    val = ch - 55;
  else if (ch >= 'a' && ch <= 'f')
    val = ch - 87;
  else if (ch >= '0' && ch <= '9')
    val = ch - 48;
  else
    val = 0x00;

  return val;  
}

/**
 * swReset
 * 
 * Software reset
 */
void swReset(void) 
{
  WDTCTL = 0;
  while (1) {}
}

