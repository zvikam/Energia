/*
  ************************************************************************
  *	pins_energia.h
  *
  *	Energia core files for MSP430
  *		Copyright (c) 2012 Robert Wessels. All right reserved.
  *
  *     Contribution: Daniel Berenguer (panStamp)
  *
  ***********************************************************************
  Derived from:
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h
#ifndef BV
#define BV(x) (1 << (x))
#endif

#if defined(__MSP430_HAS_USCI_A0__)
static const uint8_t UARTRXD = 14;  /* Receive  Data (RXD) at P3.7 */
static const uint8_t UARTTXD = 15;  /* Transmit Data (TXD) at P3.6 */
#define UARTRXD_SET_MODE (PORT_SELECTION0 | PORT_SELECTION1 | INPUT)
#define UARTTXD_SET_MODE (PORT_SELECTION0 | PORT_SELECTION1 | OUTPUT)
#endif

#if defined(__MSP430_HAS_USCI_B0__)
//Only set up for I2C right now
static const uint8_t TWISDA  = 4; /* P1.7 */
static const uint8_t TWISCL  = 5; /* P1.6 */
#define TWISDA_SET_MODE  (PORT_SELECTION0 | PORT_SELECTION1 | INPUT_PULLUP)
#define TWISCL_SET_MODE  (PORT_SELECTION0 | PORT_SELECTION1 | INPUT_PULLUP)
#endif

static const uint8_t A0  = 0;
static const uint8_t A1  = 1;
static const uint8_t A2  = 2;
static const uint8_t A3  = 3;
static const uint8_t A4  = 4;
static const uint8_t A5  = 5;  // Connected to onboard 10K NTC

//                      +----------+
//               GND   1|   ||||   |24  GND
//               P3.0  2|          |23  P1.0
//               P3.1  3|          |22  P1.1
//               P3.2  4|          |21  P1.2
//               P2.7  5|          |20  P1.3 (SPI_MOSI)
//               P2.6  6|          |19  P1.4 (SPI_MISO / I2C_SDA)
//               GND   7|          |18  P1.5 (SPI_SCK / I2C_SCL)
//          (A4) P2.4  8|          |17  P1.6 (UART_TX)
//          (A3) P2.3  9|          |16  P1.7 (UART_RX)
//          (A2) P2.2 10|          |15  GND
//          (A1) P2.1 11|          |14  VCC
//          (A0) P2.0 12|          |13  RST
//                      +----------+
//

// Pin names based on the silkscreen
//
static const uint8_t P3_0 = 2;
static const uint8_t P3_1 = 3;
static const uint8_t P3_2 = 4;

static const uint8_t P2_7 = 5;
static const uint8_t P2_6 = 6;
static const uint8_t P2_4 = 8;
static const uint8_t P2_3 = 9;
static const uint8_t P2_2 = 10;
static const uint8_t P2_1 = 11;
static const uint8_t P2_0 = 12;

static const uint8_t P1_7 = 16;
static const uint8_t P1_6 = 17;
static const uint8_t P1_5 = 18;
static const uint8_t P1_4 = 19;
static const uint8_t P1_3 = 20;
static const uint8_t P1_2 = 21;
static const uint8_t P1_1 = 22;
static const uint8_t P1_0 = 23;

static const uint8_t TEMPSENSOR = 25;
static const uint8_t ONBOARD_LED = 26;



#ifdef ARDUINO_MAIN

const uint16_t port_to_input[] = {
	NOT_A_PORT,
	(uint16_t) &P1IN,
	(uint16_t) &P2IN,
	(uint16_t) &P3IN,
	(uint16_t) &PJIN,
};

const uint16_t port_to_output[] = {
	NOT_A_PORT,
	(uint16_t) &P1OUT,
	(uint16_t) &P2OUT,
	(uint16_t) &P3OUT,
	(uint16_t) &PJOUT,
};

const uint16_t port_to_dir[] = {
	NOT_A_PORT,
	(uint16_t) &P1DIR,
	(uint16_t) &P2DIR,
	(uint16_t) &P3DIR,
	(uint16_t) &PJDIR,
};

const uint16_t port_to_ren[] = {
	NOT_A_PORT,
	(uint16_t) &P1REN,
	(uint16_t) &P2REN,
	(uint16_t) &P3REN,
	(uint16_t) NOT_A_PORT, //&PJREN
};

const uint16_t port_to_sel0[] = {
	NOT_A_PORT,
	(uint16_t) &P1SEL,
	(uint16_t) &P2SEL,
	(uint16_t) &P3SEL,
	(uint16_t) NOT_A_PORT, //&PJSEL,
};

const uint16_t port_to_pmap[] = {
	NOT_A_PORT,	/* PMAP starts at port P1 */
	(uint16_t) &P1MAP0,
	(uint16_t) &P2MAP0,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
};

/* 
 * Defines for devices with 2x TA3 timers (e.g. MSP430g2553). On the 20pin devices, upto 3 analog outputs are available
 * T0A1, T1A1 and T1A2 
 */
const uint8_t digital_pin_to_timer[] = {
	NOT_ON_TIMER, /*  dummy */
	NOT_ON_TIMER, /*  1 - GND */
	NOT_ON_TIMER, /*  2 - P3.0 */
	NOT_ON_TIMER, /*  3 - P3.1 */
	NOT_ON_TIMER, /*  4 - P3.2 */
	T1A2,         /*  5 - P2.7 */
	T1A1,         /*  6 - P2.6 */
	NOT_ON_TIMER, /*  7 - GND */
	T1A0,         /*  8 - P2.4 */
	NOT_ON_TIMER, /*  9 - P2.3 */
	NOT_ON_TIMER, /* 10 - P2.2 */
	NOT_ON_TIMER, /* 11 - P2.1 */
	NOT_ON_TIMER, /* 12 - P2.0 */
	NOT_ON_TIMER, /* 13 - RST */
	NOT_ON_TIMER, /* 14 - VCC */
	NOT_ON_TIMER, /* 15 - GND */
	NOT_ON_TIMER, /* 16 - P1.7 */  
	NOT_ON_TIMER, /* 17 - P1.6 */  
	NOT_ON_TIMER, /* 18 - P1.5 */
	T0A4,         /* 19 - P1.4 */
	T0A3,         /* 20 - P1.3 */
	T0A2,         /* 21 - P1.2 */
	T0A1,         /* 22 - P1.1 */
	T0A0,         /* 23 - P1.0 */
	NOT_ON_TIMER, /* 24 - GND */
};

const uint8_t digital_pin_to_port[] = {
	NOT_A_PIN,	 /*  dummy */
	NOT_A_PIN,   /*  1 - GND  */
	P3,          /*  2 - P3.0 */
	P3,          /*  3 - P3.1 */
	P3,		       /*  4 - P3.2 */
	P2,          /*  5 - P2.7 */
	P2,          /*  6 - P2.6 */
	NOT_A_PIN,   /*  7 - GND */
	P2,          /*  8 - P2.4 */
	P2,          /*  9 - P2.3 */
	P2,          /* 10 - P2.2 */
	P2,          /* 11 - P2.1 */
	P2,          /* 12 - P2.0 */
	NOT_A_PIN,   /* 13 - RST */
	NOT_A_PIN,   /* 14 - VCC */
	NOT_A_PIN,   /* 15 - GND */
	P1,          /* 16 - P1.7 */  
	P1,          /* 17 - P1.6 */  
	P1,          /* 18 - P1.5 */
	P1,          /* 19 - P1.4 */
	P1,          /* 20 - P1.3 */
	P1,          /* 21 - P1.2 */
	P1,          /* 22 - P1.1 */
	P1,          /* 23 - P1.0 */
	NOT_A_PIN,   /* 24 - GND */
};

const uint8_t digital_pin_to_bit_mask[] = {
	NOT_A_PIN,	 /*  dummy */
	NOT_A_PIN,   /*  1 - GND  */
	BV(0),       /*  2 - P3.0 */
	BV(1),       /*  3 - P3.1 */
	BV(2),       /*  4 - P3.2 */
	BV(7),       /*  5 - P2.7 */
	BV(6),       /*  6 - P2.6 */
	NOT_A_PIN,   /*  7 - GND */
	BV(4),       /*  8 - P2.4 */
	BV(3),       /*  9 - P2.3 */
	BV(2),       /* 10 - P2.2 */
	BV(1),       /* 11 - P2.1 */
	BV(0),       /* 12 - P2.0 */
	NOT_A_PIN,   /* 13 - RST */
	NOT_A_PIN,   /* 14 - VCC */
	NOT_A_PIN,   /* 15 - GND */
	BV(7),       /* 16 - P1.7 */  
	BV(6),       /* 17 - P1.6 */  
	BV(5),       /* 18 - P1.5 */
	BV(4),       /* 19 - P1.4 */
	BV(3),       /* 20 - P1.3 */
	BV(2),       /* 21 - P1.2 */
	BV(1),       /* 22 - P1.1 */
	BV(0),       /* 23 - P1.0 */
	NOT_A_PIN,   /* 24 - GND */
};


#endif
#endif
