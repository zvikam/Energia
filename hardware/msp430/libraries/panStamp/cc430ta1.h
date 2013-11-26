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

#ifndef _CC430TA1_H
#define _CC430TA1_H

#include "datatypes.h"

/**
 * Macros
 */
#define setTimerA1CallBack(ptrFunc)   timerA1overflow = ptrFunc

/**
 * Class: CC430TA1
 */
class CC430TA1
{
  public:
    /**
     * TA1 overflow callback function
     */
    void (*timerA1overflow)(void);

    /**
     * start
     *
     * Start TA1 timer
     *
     * @param millis Milliseconds to be timed
     */
    void start(uint32_t millis);

    /**
     * stop
     *
     * Stop TA1 timer
     */
    void stop(void);
};

#endif

