/**
 * Copyright (c) 2011 panStamp <contact@panstamp.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 11/05/2013
 */

#include "thermistor.h"

//#define VERBOSE_SENSOR_ENABLED
/**
 * Thermistor
 */
// Thermistor power pin
//#define THERMISTOR_PWRPIN 15
// which analog pin to connect
#define THERMISTORPIN A5       
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3380 //3950
// The value of the 'other' resistor
#define SERIESRESISTOR 10000
// Macros
#define powerThermistorOn()   PJOUT |= BIT2
#define powerThermistorOff()  PJOUT &= ~BIT2

/**
 * init
 * 
 * Initialize thermistor pins
 */
void THERMISTOR::init(void) 
{
  PJDIR |= BIT2;          // Set power pin as output
  powerThermistorOff();   // Unpower sensor by default

  P2DIR &= ~BIT5;         // Set analog pin as input
  P2MAP5 = PM_ANALOG;
  P2SEL |= BIT5;
}

/**
 * read
 *
 * Read temperature from thermistor
 *
 * @return temperature in 0.1 ºC
 */
int THERMISTOR::read(void)
{
  // Power thermistor circuit
  powerThermistorOn();
  delay(10);

  uint8_t i;
  uint16_t samples[NUMSAMPLES];
  float average;

  analogReference(DEFAULT);

  // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++)
  {
    samples[i] = analogRead(THERMISTORPIN);
    delay(10);
  }
 
  powerThermistorOff();
 
  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++)
     average += samples[i];
  average /= NUMSAMPLES;

  #ifdef VERBOSE_SENSOR_ENABLED  
  Serial.print("Average analog reading "); 
  Serial.println(average);
  #endif
 
  // convert the value to resistance
  average = 0xFFF / average - 1;
  average = SERIESRESISTOR * average;

  #ifdef VERBOSE_SENSOR_ENABLED
  Serial.print("Thermistor resistance "); 
  Serial.println(average);
  #endif
 
  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = logf(steinhart);                 // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C
 
  #ifdef VERBOSE_SENSOR_ENABLED
  Serial.print("Temperature "); 
  Serial.print(steinhart);
  Serial.println(" *C");
  #endif
  
  return (int)(steinhart * 10);
}

