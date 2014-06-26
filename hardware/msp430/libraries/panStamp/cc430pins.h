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
 * Creation date: 08/05/2013
 */

#ifndef _CC430PINS_H
#define _CC430OINS_H

#include "cc430f5137.h"
#include "datatypes.h"

typedef enum
{
  PM_BININP = 0,
  PM_BINOUT,
  PM_ADC,
  PM_PWM
} PINMODE;

// UART
#define pinUARTmap()      P1MAP6 = PM_UCA0TXD; P1MAP7 = PM_UCA0RXD
#define pinUARTconfig()   P1SEL |= BIT6 | BIT7;     // Set P1.6 and P1.7 to USCI Mode
// I2C
#define pinI2Cmap()       P1MAP4 = PM_UCB0SDA; P1MAP5 = PM_UCB0SCL
#define pinI2Cconfig()    P1SEL |= BIT4 | BIT5;     // Set P1.4 and P1.5 to USCI function

#define NOT_A_PIN 0

const uint16_t ioToSel[] = {
	(uint16_t) &P1SEL, 
	(uint16_t) &P1SEL,
  (uint16_t) &P1SEL,
  (uint16_t) &P1SEL,
  (uint16_t) &P1SEL,
  (uint16_t) &P1SEL,
  (uint16_t) &P1SEL,
  (uint16_t) &P1SEL,
	(uint16_t) &P2SEL,
  (uint16_t) &P2SEL,
  (uint16_t) &P2SEL,
  (uint16_t) &P2SEL,
  (uint16_t) &P2SEL,
  (uint16_t) &P2SEL,
  (uint16_t) &P2SEL,
  (uint16_t) &P2SEL,
	(uint16_t) &P3SEL,
  (uint16_t) &P3SEL,
  (uint16_t) &P3SEL,
	NOT_A_PIN,
  (uint16_t) &P3SEL
};

const uint16_t ioToMap[] = {
	(uint16_t) &P1MAP0, 
	(uint16_t) &P1MAP1,
  (uint16_t) &P1MAP2,
  (uint16_t) &P1MAP3,
  (uint16_t) &P1MAP4,
  (uint16_t) &P1MAP5,
  (uint16_t) &P1MAP6,
  (uint16_t) &P1MAP7,
	(uint16_t) &P2MAP0,
  (uint16_t) &P2MAP1,
  (uint16_t) &P2MAP2,
  (uint16_t) &P2MAP3,
  (uint16_t) &P2MAP4,
  (uint16_t) &P2MAP5,
  (uint16_t) &P2MAP6,
  (uint16_t) &P2MAP7,
	(uint16_t) &P3MAP0,
  (uint16_t) &P3MAP1,
  (uint16_t) &P3MAP2,
	NOT_A_PIN,
  (uint16_t) &P3MAP3
};

const uint16_t ioToDir[] = {
	(uint16_t) &P1DIR, 
	(uint16_t) &P1DIR,
  (uint16_t) &P1DIR,
  (uint16_t) &P1DIR,
  (uint16_t) &P1DIR,
  (uint16_t) &P1DIR,
  (uint16_t) &P1DIR,
  (uint16_t) &P1DIR,
	(uint16_t) &P2DIR,
  (uint16_t) &P2DIR,
  (uint16_t) &P2DIR,
  (uint16_t) &P2DIR,
  (uint16_t) &P2DIR,
  (uint16_t) &P2DIR,
  (uint16_t) &P2DIR,
  (uint16_t) &P2DIR,
	(uint16_t) &P3DIR,
  (uint16_t) &P3DIR,
  (uint16_t) &P3DIR,
	(uint16_t) &PJDIR,
  (uint16_t) &P3DIR
};

const uint16_t ioToIn[] = {
	(uint16_t) &P1IN, 
	(uint16_t) &P1IN,
  (uint16_t) &P1IN,
  (uint16_t) &P1IN,
  (uint16_t) &P1IN,
  (uint16_t) &P1IN,
  (uint16_t) &P1IN,
  (uint16_t) &P1IN,
	(uint16_t) &P2IN,
  (uint16_t) &P2IN,
  (uint16_t) &P2IN,
  (uint16_t) &P2IN,
  (uint16_t) &P2IN,
  (uint16_t) &P2IN,
  (uint16_t) &P2IN,
  (uint16_t) &P2IN,
	(uint16_t) &P3IN,
  (uint16_t) &P3IN,
  (uint16_t) &P3IN,
	(uint16_t) &PJIN,
  (uint16_t) &P3IN
};

const uint16_t ioToOut[] = {
	(uint16_t) &P1OUT, 
	(uint16_t) &P1OUT,
  (uint16_t) &P1OUT,
  (uint16_t) &P1OUT,
  (uint16_t) &P1OUT,
  (uint16_t) &P1OUT,
  (uint16_t) &P1OUT,
  (uint16_t) &P1OUT,
	(uint16_t) &P2OUT,
  (uint16_t) &P2OUT,
  (uint16_t) &P2OUT,
  (uint16_t) &P2OUT,
  (uint16_t) &P2OUT,
  (uint16_t) &P2OUT,
  (uint16_t) &P2OUT,
  (uint16_t) &P2OUT,
	(uint16_t) &P3OUT,
  (uint16_t) &P3OUT,
  (uint16_t) &P3OUT,
	(uint16_t) &PJOUT,
  (uint16_t) &P3OUT
};

const uint16_t ioToADC[] = {
	NOT_A_PIN, 
	NOT_A_PIN,
  NOT_A_PIN,
  NOT_A_PIN,
  NOT_A_PIN,
  NOT_A_PIN,
  NOT_A_PIN,
  NOT_A_PIN,
	0,
  1,
  2,
  3,
  4,
  5,
  NOT_A_PIN,
  NOT_A_PIN,
	NOT_A_PIN,
  NOT_A_PIN,
  NOT_A_PIN,
	NOT_A_PIN,
  NOT_A_PIN
};

const uint8_t ioToBit[] = {
  BIT0,
  BIT1,
  BIT2,
  BIT3,
  BIT4,
  BIT5,
  BIT6,
  BIT7,
  BIT0,
  BIT1,
  BIT2,
  BIT3,
  BIT4,
  BIT5,
  BIT6,
  BIT7,
  BIT0,
  BIT1,
  BIT2,
  BIT1,
  BIT3
};
#endif

/**
 * PWM config registers
 */
const uint8_t pwmToTimerPM[] = {
  PM_TA0CCR1A,
  PM_TA0CCR2A,
  PM_TA0CCR3A,
  PM_TA0CCR4A,
  PM_TA1CCR1A,
  PM_TA1CCR2A
};

