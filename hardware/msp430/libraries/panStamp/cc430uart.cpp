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
 * Creation date: 10/27/2013
 */

#include "cc430uart.h"
#include "cc430pins.h"
#include "config.h"
#include "cc430f5137.h"

bool rxAvailable = false;

/**
 * init
 * 
 * Initialize UART port
 *
 * @param baud Serial baudrate
 */
void CC430UART::init(uint16_t baud) 
{
	uint16_t ucbrf, divider;
  uint32_t clkfreq = SYSTEM_CLK_FREQ;
  /**
   * Pin mapping
   */
	PMAPPWD = 0x02D52;	  // Get write-access to port mapping regs
  PMAPCTL |= PMAPRECFG; // Leave Pin mapping open
  pinUARTmap();         // Map UART pins
	PMAPPWD = 0;		      // Lock port mapping registers

  pinUARTconfig();
/*
	UCA0CTL1 = UCSWRST;
	UCA0CTL1 = UCSSEL_2;  // SMCLK
	UCA0CTL0 = 0;
	UCA0ABCTL = 0;

  divider = (clkfreq >> 4)/baud;
  ucbrf = (clkfreq % (baud << 4)) / baud;

  UCA0BR0 = divider;                   // Integer part of UART frequency scaler (low byte)
  UCA0BR1 = divider>>8;                // Integer part of UART frequency scaler (high byte)
  UCA0MCTL = ucbrf + UCBRS_0 + UCOS16; // This turns on oversampling and sets the decimal part of the scaler

	UCA0CTL1 &= ~UCSWRST;
	UCA0IE |= UCRXIE | UCTXIE;           // Enable Rx and Tx interrupts
*/
}

/**
 * send
 * 
 * Send data buffer
 *
 * @param buf Buffer to be sent
 * @param len Amount of bytes to be transferred
 *
 * @return Amount of bytes transmitted
 */
uint16_t CC430UART::send(uint8_t *buf, uint16_t len) 
{
  uint16_t i, res = len;

  while (!(UCA0IFG & UCTXIFG));

  // Send bytes
  for(i=0 ; i<len ; i++)
  {
    UCA0TXBUF = buf[i];
    while (!(UCA0IFG & UCTXIFG));
  }

  return res;
}

/**
 * receive
 * 
 * Read string from the Rx FIFO
 *
 * @param buf Buffer to be sent
 *
 * @return amount of bytes read or -1 if the Rx FIFO is empty
 */
int CC430UART::receive(uint8_t *buf) 
{
  int i = -1;

  while(UCA0IFG & UCRXIFG)
    buf[++i] = UCA0RXBUF;

  buf[i+1] = 0;

  rxAvailable = false;
  return i;
}

/**
 * uartISR
 *
 * UART interrupt routine
 */
#ifndef Energia_h
__attribute__((interrupt(USCI_A0_VECTOR)))
void uartISR(void)
{
  switch (UCA0IV) 
  { 
    case USCI_UCRXIFG:
      while (!(UCA0IFG&UCTXIFG));           // USCI_A0 TX buffer ready?
      rxAvailable = true;
      break;
    default:
      break;
  }
}
#endif

