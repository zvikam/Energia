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

static const uint8_t DEBUG_UARTTXD = 6;  /* Transmit Data (TXD) at P1.6 */
static const uint8_t DEBUG_UARTRXD = 7;  /* Receive  Data (RXD) at P1.7 */
#define DEBUG_UARTRXD_SET_MODE (PORT_SELECTION0 | (PM_UCA0RXD << 8) | INPUT)
#define DEBUG_UARTTXD_SET_MODE (PORT_SELECTION0 | (PM_UCA0TXD << 8) | OUTPUT)

static const uint8_t TWISDA  = 4; /* P1.4 */
static const uint8_t TWISCL  = 5; /* P1.5 */
#define TWISDA_SET_MODE  (PORT_SELECTION0 | (PM_UCB0SDA << 8) | INPUT_PULLUP)
#define TWISCL_SET_MODE  (PORT_SELECTION0 | (PM_UCB0SCL << 8) | INPUT_PULLUP)

static const uint8_t SS      = 2; /* P1.2 */
static const uint8_t MOSI    = 3; /* P1.3 */
static const uint8_t MISO    = 4; /* P1.4 */
static const uint8_t SCK     = 5; /* P1.5 */
#define SPISCK_SET_MODE (PORT_SELECTION0 | (PM_UCB0CLK << 8))
#define SPIMOSI_SET_MODE (PORT_SELECTION0 | (PM_UCB0SIMO << 8))
#define SPIMISO_SET_MODE (PORT_SELECTION0 | (PM_UCB0SOMI << 8))

// Debug UART is on USCIA0 so offset is 0
#define DEBUG_UART_MODULE_OFFSET 0x0

static const uint8_t A0  = 0;
static const uint8_t A1  = 1;
static const uint8_t A2  = 2;
static const uint8_t A3  = 3;
static const uint8_t A4  = 4;
static const uint8_t A5  = 5;  // Connected to onboard 10K NTC

//                      +-----------+
//               GND   1|    ||||   |24  GND
//         (D16) P3.0  2|           |23  P1.0 (D0)
//   (PWM) (D17) P3.1  3|           |22  P1.1 (D1)
//   (PWM) (D18) P3.2  4|           |21  P1.2 (D2) (PWM)
//         (D15) P2.7  5|           |20  P1.3 (SPI_MOSI) (D3) (PWM)
//         (D14) P2.6  6|           |19  P1.4 (SPI_MISO / I2C_SDA) (D4) (PWM)
//               GND   7|           |18  P1.5 (SPI_SCK / I2C_SCL) (D5) (PWM)
//      (D12/A4) P2.4  8|           |17  P1.6 (UART_TX) (D6)
//      (D11/A3) P2.3  9|           |16  P1.7 (UART_RX) (D7)
//      (D10/A2) P2.2 10|           |15  GND
//       (D9/A1) P2.1 11|           |14  VCC
//       (D8/A0) P2.0 12|           |13  RST
//                      +-----------+
//                      | | | | | | |
//                   P2.0 | | | | | RST
//                      VCC | | | TST
//                        GND | TX
//                            RX
//
//                  TEMPSENSOR  -- P2.5
//                  ONBOARD_LED -- PJ.1

// Pin names based on the silkscreen
//
static const uint8_t P3_0 = 16;
static const uint8_t P3_1 = 17;
static const uint8_t P3_2 = 18;

static const uint8_t P2_7 = 15;
static const uint8_t P2_6 = 14;
static const uint8_t P2_4 = 12;
static const uint8_t P2_3 = 11;
static const uint8_t P2_2 = 10;
static const uint8_t P2_1 = 9;
static const uint8_t P2_0 = 8;

static const uint8_t P1_7 = 7;
static const uint8_t P1_6 = 6;
static const uint8_t P1_5 = 5;
static const uint8_t P1_4 = 4;
static const uint8_t P1_3 = 3;
static const uint8_t P1_2 = 2;
static const uint8_t P1_1 = 1;
static const uint8_t P1_0 = 0;

static const uint8_t TEMPSENSOR = 13;
static const uint8_t ONBOARD_LED = 19;



#ifdef ARDUINO_MAIN

const uint16_t port_to_input[] = {
	NOT_A_PORT,
	(uint16_t) &P1IN,
	(uint16_t) &P2IN,
	(uint16_t) &P3IN,
	(uint16_t) &P5IN,
	(uint16_t) &PJIN,
};

const uint16_t port_to_output[] = {
	NOT_A_PORT,
	(uint16_t) &P1OUT,
	(uint16_t) &P2OUT,
	(uint16_t) &P3OUT,
	(uint16_t) &P5OUT,
	(uint16_t) &PJOUT,
};

const uint16_t port_to_dir[] = {
	NOT_A_PORT,
	(uint16_t) &P1DIR,
	(uint16_t) &P2DIR,
	(uint16_t) &P3DIR,
	(uint16_t) &P5DIR,
	(uint16_t) &PJDIR,
};

const uint16_t port_to_ren[] = {
	NOT_A_PORT,
	(uint16_t) &P1REN,
	(uint16_t) &P2REN,
	(uint16_t) &P3REN,
	(uint16_t) &P5REN,
	(uint16_t) NOT_A_PORT, //No PJREN
};

const uint16_t port_to_sel0[] = {
	NOT_A_PORT,
	(uint16_t) &P1SEL,
	(uint16_t) &P2SEL,
	(uint16_t) &P3SEL,
	(uint16_t) NOT_A_PORT, // No P5SEL
	(uint16_t) NOT_A_PORT, // No PJSEL,
};

const uint16_t port_to_pmap[] = {
	NOT_A_PORT,	/* PMAP starts at port P1 */
	(uint16_t) &P1MAP0,
	(uint16_t) &P2MAP0,
	(uint16_t) &P3MAP0,
	NOT_A_PORT, // No P5MAP0
	NOT_A_PORT, // No PJMAP0
};

const uint8_t digital_pin_to_timer[] = {
	NOT_ON_TIMER, /* P1.0 */
	T0A0,         /* P1.1 - note: A0 output cannot be used with analogWrite */
	T0A1,         /* P1.2 */
	T0A2,         /* P1.3 */
	T0A3,         /* P1.4 */
	T0A4,         /* P1.5 */
	NOT_ON_TIMER, /* P1.6 */
	NOT_ON_TIMER, /* P1.7 */
	NOT_ON_TIMER, /* P2.0 */
	NOT_ON_TIMER, /* P2.1 */
	NOT_ON_TIMER, /* P2.2 */
	NOT_ON_TIMER, /* P2.3 */
	NOT_ON_TIMER, /* P2.4 */
	NOT_ON_TIMER, /* TEMPSENSOR */
	NOT_ON_TIMER, /* P2.6 */
	NOT_ON_TIMER, /* P2.7 */
	T1A0,         /* P3.0 - note: A0 output cannot be used with analogWrite */
	T1A1,         /* P3.1 */
	T1A2,         /* P3.2 */
	NOT_ON_TIMER, /* ONBOARD_LED */
};

const uint8_t digital_pin_to_port[] = {
	P1,           /* P1.0 */
	P1,           /* P1.1 */
	P1,           /* P1.2 */
	P1,           /* P1.3 */
	P1,           /* P1.4 */
	P1,           /* P1.5 */
	P1,           /* P1.6 */
	P1,           /* P1.7 */
	P2,           /* P2.0 */
	P2,           /* P2.1 */
	P2,           /* P2.2 */
	P2,           /* P2.3 */
	P2,           /* P2.4 */
	P2,           /* TEMPSENSOR */
	P2,           /* P2.6 */
	P2,           /* P2.7 */
	P3,           /* P3.0 */
	P3,           /* P3.1 */
	P3,           /* P3.2 */
	PJ,           /* ONBOARD_LED */
};

const uint8_t digital_pin_to_bit_mask[] = {
	BV(0),        /* P1.0 */
	BV(1),        /* P1.1 */
	BV(2),        /* P1.2 */
	BV(3),        /* P1.3 */
	BV(4),        /* P1.4 */
	BV(5),        /* P1.5 */
	BV(6),        /* P1.6 */
	BV(7),        /* P1.7 */
	BV(0),        /* P2.0 */
	BV(1),        /* P2.1 */
	BV(2),        /* P2.2 */
	BV(3),        /* P2.3 */
	BV(4),        /* P2.4 */
	BV(5),        /* TEMPSENSOR */
	BV(6),        /* P2.6 */
	BV(7),        /* P2.7 */
	BV(0),        /* P3.0 */
	BV(1),        /* P3.1 */
	BV(2),        /* P3.2 */
	BV(1),        /* ONBOARD_LED */
};

const uint32_t digital_pin_to_analog_in[] = {
	NOT_ON_ADC,   /* P1.0 */
	NOT_ON_ADC,   /* P1.1 */
	NOT_ON_ADC,   /* P1.2 */
	NOT_ON_ADC,   /* P1.3 */
	NOT_ON_ADC,   /* P1.4 */
	NOT_ON_ADC,   /* P1.5 */
	NOT_ON_ADC,   /* P1.6 */
	NOT_ON_ADC,   /* P1.7 */
	0,            /* P2.0 */
	1,            /* P2.1 */
	2,            /* P2.2 */
	3,            /* P2.3 */
	4,            /* P2.4 */
	5,            /* TEMPSENSOR */
	NOT_ON_ADC,   /* P2.6 */
	NOT_ON_ADC,   /* P2.7 */
	NOT_ON_ADC,   /* P3.0 */
	NOT_ON_ADC,   /* P3.1 */
	NOT_ON_ADC,   /* P3.2 */
	NOT_ON_ADC,   /* ONBOARD_LED */
};

/* MSP430's with Port Mappers (F5xxx series, etc) need the correct Port Mapping ID for their timers. */
const uint8_t pmap_timer_ids[] = {
   9,	 // T0A0
   10, // T0A1
   11, // T0A2
   12, // T0A3
   13, // T0A4
   14, // T1A0
   15, // T1A1
   16, // T1A2
   0,	 // T1A3
   0,	 // T1A4
   0,	 // T1A5
   0,	 // T2A0
   0,	 // T2A1
   0,	 // T2A2
   0,	 // T0B0
   0,	 // T0B1
   0,	 // T0B2
   0,	 // T0B3
   0,	 // T0B4
   0,	 // T0B5
   0,	 // T0B6
   0,	 // T1B0
   0,	 // T1B1
   0,	 // T1B2
   0,	 // T2B0
   0,	 // T2B1
   0,	 // T2B2
};


#endif
#endif
