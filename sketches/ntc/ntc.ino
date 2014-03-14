/*
 * temphum
 *
 * Copyright (c) 2011 Daniel Berenguer <dberenguer@usapiens.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
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
 * Creation date: 02/24/2014
 *
 * Device:
 * Temperature sensor
 *
 * Description:
 * This is a basic device measuring temperature from the onboard 10Kohm
 * NTC thermistor
 *
 * Thos device is low-power enabled so it will enter low-power mode
 * just after reading the sensor value and transmitting it over the
 * SWAP network.
 *
 * Associated Device Definition Files, defining registers, endpoints and
 * configuration parameters:
 * temp.xml (Temperature sensor)
 */
 
#include "regtable.h"
#include "panstamp.h"

/**
 * Uncomment if you are reading Vcc from A7. All battery-boards do this
 */
//#define VOLT_SUPPLY_A0


/**
 * setup
 *
 * Arduino setup function
 */
void setup()
{
  int i;

  // Init panStamp
  panstamp.init();

  // Transmit product code
  getRegister(REGI_PRODUCTCODE)->getData();

  // Enter SYNC state
  panstamp.enterSystemState(SYSTATE_SYNC);

  // During 3 seconds, listen the network for possible commands whilst the LED blinks
  for(i=0 ; i<6 ; i++)
  {
    digitalWrite(ONBOARD_LED, HIGH);
    delay(100);
    digitalWrite(ONBOARD_LED, LOW);
    delay(400);
  }

  // Transmit periodic Tx interval
  getRegister(REGI_TXINTERVAL)->getData();
  
   // Switch to Rx OFF state
  panstamp.enterSystemState(SYSTATE_RXOFF);
}

/**
 * loop
 *
 * Arduino main loop
 */
void loop()
{
  digitalWrite(ONBOARD_LED, HIGH);
  // Transmit sensor data
  getRegister(REGI_VOLTSUPPLY)->getData();
  // Transmit power voltage
  getRegister(REGI_SENSOR)->getData();
  digitalWrite(ONBOARD_LED, LOW);

  // Sleep
  panstamp.goToSleep();
}

