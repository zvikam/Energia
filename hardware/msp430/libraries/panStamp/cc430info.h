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
 * Creation date: 10/23/2013
 */

#ifndef _CC430INFO_H
#define _CC430INFO_H

#include "config.h"
#include "datatypes.h"

/**
 * Infomem addresses
 */
#define INFOMEM_FREQ_CHANNEL       0x00   // 1-byte register
#define INFOMEM_NOT_USED           0x01   // 1-byte register
#define INFOMEM_SYNC_WORD          0x02   // 2-byte register
#define INFOMEM_DEVICE_ADDR        0x04   // 1 or 2 byte register
#define INFOMEM_TX_INTERVAL        0x06   // 2-byte register
#define INFOMEM_FIRST_CUSTOM       0x20

#ifdef SWAP_EXTENDED_ADDRESS
#define INFOMEM_DEVICE_ADDRESS     INFOMEM_DEVICE_ADDR
#else
#define INFOMEM_DEVICE_ADDRESS     INFOMEM_DEVICE_ADDR + 1
#endif

class CC430INFO
{
  public:
    /**
     * read
     * 
     * Read buffer from info memory
     *
     * @param buffer pointer to the buffer where to write the result
     * @param section info memory section (A, B, C or D)
     * @param position position in section
     * @pararm length Length to be read
     *
     * @return amount of bytes read
     */
    uint8_t read(uint8_t *buffer, char section, uint8_t position, uint8_t length);

    /**
     * write
     * 
     * Write buffer in info memory
     *
     * @param buffer array to be written
     * @param section info memory section (A, B, C or D)
     * @param position position in section
     * @pararm length Length to be written
     *
     * @return amount of bytes copied
     */
    uint8_t write(uint8_t *buffer, char section, uint8_t position, uint8_t length);
};

#endif
