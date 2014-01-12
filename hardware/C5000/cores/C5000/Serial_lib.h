//////////////////////////////////////////////////////////////////////////////
// *
// * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// *
// *
// *  Redistribution and use in source and binary forms, with or without
// *  modification, are permitted provided that the following conditions
// *  are met:
// *
// *    Redistributions of source code must retain the above copyright
// *    notice, this list of conditions and the following disclaimer.
// *
// *    Redistributions in binary form must reproduce the above copyright
// *    notice, this list of conditions and the following disclaimer in the
// *    documentation and/or other materials provided with the
// *    distribution.
// *
// *    Neither the name of Texas Instruments Incorporated nor the names of
// *    its contributors may be used to endorse or promote products derived
// *    from this software without specific prior written permission.
// *
// *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// *
//////////////////////////////////////////////////////////////////////////////
/** @file Serial_lib.h
 *
 *  @brief Serial library header file
 *
 */

#ifndef Serial_h
#define Serial_h

#include "csl_uart.h"
#include "csl_pll.h"
#include "csl_sysctrl.h"
#include <string.h>

/** \brief  Enumeration for number format
*/
typedef enum NUMBER_FORMAT
{
    BIN,   /**< Enum to represent Binary Number Form        */
    DEC,   /**< Enum to represent Decimal Number Form       */
    OCT,   /**< Enum to represent Octal Decimal Number Form */
    HEX    /**< Enum to represent Hexadecimal Number Form   */
} NUMBER_FORMAT;

/**
 * \brief Baudrate configuration Class
 *
 *  Contains variables used to configure serial baudrate
 */
class Baudrate_Config
{
    public:
        int data;     /**< No of data bits for Serial Port   */
        int parity;   /**< No of parity bits for Serial Port */
        int stopBits; /**< No of stop bits for Serial Port   */
};

/**
 * \brief Serial Class
 *
 *  Contains prototypes for functions in Serial library
 */
class SerialClass
{
    private:
        static int         isInitialized;
        static CSL_UartObj uartObj;
        static long        timeOut;

    public:
        SerialClass();
        void begin(long baudRate);
        void begin(long baudRate, Baudrate_Config *config);
        void end(void);
        Bool find(char *target);
        Bool findUntil(char *target, char* terminal);
        void flush(void);
        float parseFloat(void);
        long parseInt(void);
        long print(int value);
        long print(unsigned int value);
        long print(short value);
        long print(unsigned short value);
        long print(long value);
        long print(unsigned long value);
        long print(float value);
        long print(double value);
        long print(char character);
        long print(char *printString);
        long print(int value, int format);
        long print(unsigned int value, int format);
        long print(short value, int format);
        long print(unsigned short value, int format);
        long print(long value, int format);
        long print(unsigned long value, int format);
        long print(float value, int noOfDecDigits);
        long print(double value, int noOfDecDigits);
        long println(int value);
        long println(unsigned int value);
        long println(short value);
        long println(unsigned short value);
        long println(long value);
        long println(unsigned long value);
        long println(float value);
        long println(double value);
        long println(char character);
        long println(char *printString);
        long println(int value, int format);
        long println(unsigned int value, int format);
        long println(short value, int format);
        long println(unsigned short value, int format);
        long println(long value, int format);
        long println(unsigned long value, int format);
        long println(float value, int noOfDecDigits);
        long println(double value, int noOfDecDigits);
        int read(void);
        int readBytes(char *buffer, int length);
        int readBytesUntil(char termChar, char *buffer, int length);
        void setTimeout(long);
        int write(int value);
        int write(char *string);
        int write(char *string, int length);
};

extern SerialClass Serial;
/**< Serial class instance extern which can used by application programs
 *   to access Serial DSP APIs
 */
#endif /* #ifndef Serial_h */
