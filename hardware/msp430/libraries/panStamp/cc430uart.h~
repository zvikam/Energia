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

#ifndef _CC430UART_H
#define _CC430UART_H

#include "datatypes.h"

class CC430UART
{
  public:
  /**
   * init
   * 
   * Initialize UART port
   *
   * @param baud Serial baudrate
   */
  void init(uint16_t baud);

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
  uint16_t send(uint8_t *buf, unsigned int len);

  /**
   * receive
   * 
   * Read string from the Rx FIFO
   *
   * @param buf Buffer to be sent
   *
   * @return amount of bytes read or -1 if the Rx FIFO is empty
   */
  int receive(uint8_t *buf);
  };

#endif

