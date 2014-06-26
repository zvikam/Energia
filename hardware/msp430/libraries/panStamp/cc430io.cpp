/**
 * Copyright (c) 2014 panStamp <contact@panstamp.com>
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
 * Creation date: 06/25/2014
 */

#include "cc430io.h"
#include "cc430pins.h"
#include "cc430f5137.h"

#define PWM_PERIOD  SYSTEM_CLK_FREQ/490

static uint8_t nextTimer = 0;
  
/**
 * CC430IO
 * 
 * Class constructor
 * 
 * @param pos Position of pin in module. From 0 to N
 */
CC430IO::CC430IO(uint8_t pos) 
{
  position = pos;
}

/**
 * init
 * 
 * Initialize i/o pins
 * 
 * @param mode pin mode: PM_BININP, PM_BINOUT, PM_ADC, PM_PWM
 */
void CC430IO::init(uint8_t mode) 
{
  pinMode = mode;
 
  volatile uint16_t *dir = (volatile uint16_t *)ioToDir[position];
  volatile uint16_t *sel = (volatile uint16_t *)ioToSel[position];
  volatile uint16_t *map = (volatile uint16_t *)ioToMap[position];
  
  switch(mode)
  {
    case PM_ADC:
      *sel |= ioToBit[position];                      // Select alternate function
      break;
    case PM_PWM:
      PMAPPWD = 0x02D52;                              // Get write-access to port mapping regs 
      *map = pwmToTimerPM[nextTimer++];               // Map pin to TAxCCRn function
      PMAPCTL |= PMAPRECFG;                           // Leave Pin mapping open
      PMAPPWD = 0;                                    // Lock port mapping registers 
      *dir |= ioToBit[position];                      // Config pin as an output
      *sel |= ioToBit[position];                      // Select alternate function
      break;
    case PM_BININP:
      *dir &= ~ioToBit[position];                     // Config pin as an input
      *sel &= ~ioToBit[position];                     // Unselect alternate function
      break;
    default: // PM_BINOUT
      *dir |= ioToBit[position];                      // Config pin as an output
      *sel &= ~ioToBit[position];                     // Unselect alternate function
      break;
  }
}

/**
 * readState
 *
 * read binary state
 *
 * @return input state
 */
uint8_t CC430IO::readState(void)
{
  volatile uint16_t *input = (volatile uint16_t *)ioToIn[position];
   
  return ((*input) & ioToBit[position] > 0);
}

/**
 * writeState
 *
 * set binary state
 *
 * @param state output state
 */
void CC430IO::writeState(uint8_t state)
{
  volatile uint16_t *out = (volatile uint16_t *)ioToOut[position];
  
  if (state)
    *out |= ioToBit[position];
  else
    *out &= ~ioToBit[position];
}

/**
 * readAnalog
 *
 * read ADC value
 *
 * @return ADC value
 */
uint16_t CC430IO::readAnalog(void)
{
  volatile uint16_t *input = (volatile uint16_t *)ioToIn[position];
   
  return ((*input) & ioToBit[position] > 0);
 
  REFCTL0 |= REFON;                               // Enable ADC reference, in case we need it
  ADC12CTL0 = ADC12SHT02 + ADC12ON;               // Sampling time=64 cycles, ADC12 on
  ADC12CTL1 = ADC12SHP;                           // Use sampling timer
  ADC12IE = ADC12IE0;                             // Enable interrupt
  ADC12MCTL0 |= ioToADC[position];                // Select channel
  ADC12CTL0 |= ADC12ON | ADC12ENC | ADC12SC;      // Enable ADC and start conversion

  __delay_cycles(250);

  while (!(ADC12IFG & BIT0));                     // Wait until ADC is completed

  ADC12IFG = 0;

  // POWER: Turn ADC and reference voltage off to conserve power
  ADC12CTL0 &= ~(ADC12ON);
  REFCTL0 &= ~REFON;
  
  return ADC12MEM0;
}

/**
 * setADCreference
 *
 * set ADC reference
 *
 * @param ref ADC reference: ADCREF_VCC, ADCREF_1V5, ADCREF_2V0 or ADCREF_2V5
 */
void CC430IO::setADCreference(uint8_t ref)
{
  if (ref == ADCREF_VCC)
      ADC12MCTL0 = ADC12SREF_0;  // Vr+=Vcc and Vr-=AVss
  else
  {
    // Enable shared reference, disable temperature sensor to save power
    REFCTL0 |= REFMSTR + ref + REFON + REFTCOFF;
    ADC12MCTL0 = ADC12SREF_1;  // Vr+=Vref+ and Vr-=AVss
  }
}

/**
 * writePWM
 *
 * set PWM output level
 *
 * @param dutyCycle duty cycle
 */
void CC430IO::writePWM(uint16_t dutyCycle)
{
  if (dutyCycle == 0)
  {
    init(PM_BINOUT);
    writeState(LOW);
  }
  else
  {
    if (pinMode != PM_PWM)
      init(PM_PWM);
      
    volatile uint16_t *map = (volatile uint16_t *)ioToMap[position];

    *map = pwmToTimerPM[nextTimer++];           // Current pin mapping
    
    switch(*map)
    {
      case PM_TA0CCR1A:
        TA0CCTL1 = OUTMOD_7;                    // CCR1 reset/set
        TA0CCR1 = dutyCycle;                    // CCR1 PWM duty cycle
        break;
      case PM_TA0CCR2A:
        TA0CCTL2 = OUTMOD_7;                    // CCR1 reset/set
        TA0CCR2 = dutyCycle;                    // CCR1 PWM duty cycle
        break;
      case PM_TA0CCR3A:
        TA0CCTL3 = OUTMOD_7;                    // CCR1 reset/set
        TA0CCR3 = dutyCycle;                    // CCR1 PWM duty cycle
        break;
      case PM_TA0CCR4A:
        TA0CCTL4 = OUTMOD_7;                    // CCR1 reset/set
        TA0CCR4 = dutyCycle;                    // CCR1 PWM duty cycle
        break;
      case PM_TA1CCR1A:
        TA1CCTL1 = OUTMOD_7;                    // CCR1 reset/set
        TA1CCR1 = dutyCycle;                    // CCR1 PWM duty cycle
        break;
      case PM_TA1CCR2A:
        TA1CCTL2 = OUTMOD_7;                    // CCR1 reset/set
        TA1CCR2 = dutyCycle;                    // CCR1 PWM duty cycle
        break;
      default:
        break;
    }
      
    if (*map < PM_TA1CCR1A)
    {
      if (dutyCycle == TA0CCR0)               // duty cycle = period?
      {
        init(PM_BINOUT);
        writeState(HIGH);
      }
      else
        TA0CTL = TASSEL_2 + MC_1 + TACLR;     // SMCLK, up mode, clear TAR
    }
    else
    {
      if (dutyCycle == TA1CCR0)               // duty cycle = period?
      {
        init(PM_BINOUT);
        writeState(HIGH);
      }
      else
        TA1CTL = TASSEL_2 + MC_1 + TACLR;     // SMCLK, up mode, clear TAR
    }
  }
}

/**
 * setPWMperiod
 *
 * set PWM period
 *
 * @param period PWM period
 */
void CC430IO::setPWMperiod(uint16_t period)
{
  volatile uint16_t *map = (volatile uint16_t *)ioToMap[position];

  *map = pwmToTimerPM[nextTimer++];         // Current pin mapping
  
  if (*map < PM_TA1CCR1A)
    TA0CCR0 = period;
  else
    TA1CCR0 = period;
}
