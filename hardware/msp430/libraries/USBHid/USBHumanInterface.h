/* --COPYRIGHT--,BSD
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/*
 USBHumanInterface.h - Library for transmitting and receiving characters 
                       through USB HID interface
*/
#ifndef USBHumanInterface_h
#define USBHumanInterface_h

#include <inttypes.h>

/******************************************************************************
 * Definitions
 ******************************************************************************/


class USBHumanInterface{
private:


  // static data

  // private methods

public:
	// public methods
	USBHumanInterface(uint16_t port);
	void HID_setup(void);
	int HID_start(void);
	uint16_t HID_receiveDataFromHost(uint8_t *dataBuffer, uint16_t buffer_size);
	uint8_t HID_sendDataToHost(uint8_t *dataBuffer, uint16_t count);
	uint8_t HID_abortDataToHost(uint16_t *size, uint8_t intfNum);
	uint8_t HID_rejectDataFromHost(uint8_t intfNum);
	uint8_t HID_abortDataFromHost(uint16_t *size, uint8_t intfNum);
 };

#endif




