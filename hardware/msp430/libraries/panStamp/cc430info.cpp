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

#include "cc430info.h"
#include "cc430x513x.h"

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
uint8_t CC430INFO::read(uint8_t *buffer, char section, uint8_t position, uint8_t length)
{
  if ((position + length) > 128)
    return 0;                           // out of range

  uint16_t i;
  char * flashPtr;                      // Initialize Flash pointer

  switch (section)
  {
    case 'A':
      flashPtr = (char *) 0x1980;
      break;
    case 'B':
      flashPtr = (char *) 0x1900;
      break;
    case 'C':
      flashPtr = (char *) 0x1880;
      break;
    case 'D':
      flashPtr = (char *) 0x1800;
      break;
    default:
      break;
  }

  flashPtr += position;

  for (i = 0; i < length; i++)
    buffer[i] = *flashPtr++;

  return length;
}

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
uint8_t CC430INFO::write(uint8_t *buffer, char section, uint8_t position, uint8_t length)
{
  if ((position + length) > 128)
    return 0;                           // out of range

  uint8_t buf[128];
  uint16_t i, j;
  char * flashPtr;                      // Initialize Flash pointer

  switch (section)
  {
    case 'A':
      flashPtr = (char *) 0x1980;
      break;
    case 'B':
      flashPtr = (char *) 0x1900;
      break;
    case 'C':
      flashPtr = (char *) 0x1880;
      break;
    case 'D':
      flashPtr = (char *) 0x1800;
      break;
    default:
      break;
  }

  for (i = 0; i < 128; i++)
    buf[i] = flashPtr[i];                // Save current contents in temporary buffer

  __disable_interrupt();                 // 5xx Workaround: Disable global
                                         // interrupt while erasing
  FCTL3 = FWKEY;                         // Clear Lock bit
  FCTL1 = FWKEY+ERASE;                   // Set Erase bit
  *flashPtr = 0;                         // Dummy write to erase Flash seg
  FCTL1 = FWKEY+WRT;                     // Set WRT bit for byte write operation

  for (i = 0; i < 128; i++)
  {
    if (i == position)
    {
      for (j = 0; j < length; j++)
        *flashPtr++ = buffer[j];         // Write byte to flash
      i += length-1;
    }
    else
      *flashPtr++ = buf[i];              // Write byte to flash
  }

  FCTL1 = FWKEY;                         // Clear WRT bit
  FCTL3 = FWKEY+LOCK;                    // Set LOCK bit

  __enable_interrupt();                  // Re-enable interrupts

  return length;
}

