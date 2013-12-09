//////////////////////////////////////////////////////////////////////////////
// *
// * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// * Copyright (C) 2011 Spectrum Digital, Incorporated
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

/** @file debug_msg.cpp
 *
 *  @brief Debug messages implementation
 *
 */
 
/**
 *
 *  dbgMsgPrint
 *
 *  API to Print an Integer to the serial port as human-readable ASCII text
 *
 *  long value <-- Integer value that is to be printed on the serial
 */
void dbgMsgPrint(long value)
{
#ifdef ENABLE_DEBUG_MSG
    Serial.print(value);
#endif
}

/**
 *
 *  dbgMsgPrint
 *
 *  API to Print a Floating Point Value to the serial port as human-readable ASCII text
 *
 *  float value <-- Floating Point value that is to be printed on the serial
 */
void dbgMsgPrint(float value)
{
#ifdef ENABLE_DEBUG_MSG
    Serial.print(value);
#endif
}

/**
 *
 *  dbgMsgPrint
 *
 *  API to Print a character to the serial port as human-readable ASCII text
 *
 *  char character <-- Character value that is to be printed on the serial
 */
void dbgMsgPrint(char character)
{
#ifdef ENABLE_DEBUG_MSG
    Serial.print(character);
#endif
}

/**
 *
 *  dbgMsgPrint
 *
 *  API to Print a String to the serial port as human-readable ASCII text
 *
 *  char *printString <-- The String that is to be printed on the serial
 */
void dbgMsgPrint(char *printString)
{
#ifdef ENABLE_DEBUG_MSG
    Serial.print(printString);
#endif
}

/**
 *
 *  dbgMsgPrintln
 *
 *  API to Print an Integer to the serial port as human-readable ASCII text,
 *  followed by a new line ("\r\n")
 *
 *  long value <-- Integer value that is to be printed on the serial
 */
void dbgMsgPrintln(long value)
{
#ifdef ENABLE_DEBUG_MSG
    Serial.println(value);
#endif
}

/**
 *
 *  dbgMsgPrintln
 *
 *  API to Print a Floating Point Value to the serial port as human-readable
 *  ASCII text, followed by a new line ("\r\n")
 *
 *  float value <-- Floating Point value that is to be printed on the serial
 */
void dbgMsgPrintln(float value)
{
#ifdef ENABLE_DEBUG_MSG
    Serial.println(value);
#endif
}

/**
 *
 *  dbgMsgPrintln
 *
 *  API to Print a character to the serial port as human-readable ASCII text,
 *  followed by a new line ("\r\n")
 *
 *  char character <-- Character value that is to be printed on the serial
 */
void dbgMsgPrintln(char character)
{
#ifdef ENABLE_DEBUG_MSG
    Serial.println(character);
#endif
}

/**
 *
 *  dbgMsgPrintln
 *
 *  API to Print an String to the serial port as human-readable ASCII text,
 *  followed by a new line ("\r\n")
 *
 *  char *printString <-- The String that is to be printed on the serial
 */
void dbgMsgPrintln(char *printString)
{
#ifdef ENABLE_DEBUG_MSG
    Serial.println(printString);
#endif
}
