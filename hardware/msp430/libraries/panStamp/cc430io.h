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

#ifndef _CC430IO_H
#define _CC430IO_H

#include "datatypes.h"

#define ADCREF_VCC  0
#define ADCREF_1V5  REFVSEL_0
#define ADCREF_2V0  REFVSEL_1
#define ADCREF_2V5  REFVSEL_2

class CC430IO
{
  public:
    /**
     * Position of pin in module. From 0 to N
     */
    uint8_t position;
    
    /**
     * Pin mode
     */
    uint8_t pinMode;
   
    /**
     * CC430IO
     * 
     * Class constructor
     * 
     * @param pos Position of pin in module. From 0 to N
     */
    CC430IO(uint8_t pos);
    
    /**
     * init
     * 
     * Initialize i/o pins
     * 
     * @param mode pin mode: PM_BININP, PM_BINOUT, PM_ADC, PM_PWM
     */
    void init(uint8_t mode);
    
    /**
     * readState
     *
     * read binary state
     *
     * @return input state
     */
    uint8_t readState(void);

    /**
     * writeState
     *
     * set binary state
     *
     * @param state output state
     */
    void writeState(uint8_t state);

    /**
     * readAnalog
     *
     * read ADC value
     *
     * @return ADC value
     */
    uint16_t readAnalog(void);

    /**
     * setADCreference
     *
     * set ADC reference
     *
     * @param ref ADC reference: ADCREF_VCC, ADCREF_1V5, ADCREF_2V0 or ADCREF_2V5
     */
    void setADCreference(uint8_t ref);

    /**
     * writePWM
     *
     * set PWM output level
     *
     * @param dutyCycle duty cycle
     */
    void writePWM(uint16_t dutyCycle);
    
    /**
     * setPWMperiod
     *
     * set PWM period
     *
     * @param period PWM period
     */
    void setPWMperiod(uint16_t period);
};

#endif

