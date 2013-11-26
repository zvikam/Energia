/**
 * Copyright (c) 2013 panStamp <contact@panstamp.com>
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
 * Creation date: 11/18/2013
 */

#include "cc430ta1.h"
#include "cc430f5137.h"

/**
 * ta1ISR
 * 
 * TimerA 1 ISR function
 */
__attribute__((interrupt(TIMER1_A0_VECTOR)))
void TIMER1_A0_ISR(void)
{
  //timerA1overflow();                        // Call user function
}

/**
 * start
 *
 * Start TA1 timer
 *
 * @param millis Milliseconds to be timed
 */
void CC430TA1::start(uint32_t millis)
{
  TA1CCTL0 = CCIE;                          // CCR0 interrupt enabled
  TA1CCR0 = 65.535 * millis;                // Max count
  TA1CTL = TASSEL_1 + MC_1 + TACLR;         // ACLK, upmode, clear TAR
}

/**
 * stop
 *
 * Stop TA1 timer
 */
void CC430TA1::stop(void)
{
  TA1CTL = MC_0;                            // Halt timer
}

