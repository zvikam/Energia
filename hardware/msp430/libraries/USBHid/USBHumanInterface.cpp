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
 USBHumanInterface.cpp - Library for transmitting and receiving characters 
                         through USB HID interface
*/

#include "Energia.h"
#include "USBHumanInterface.h"
#include "utility/driverlib.h"
#include "descriptors.h"
#include "device.h"
#include "usb.h"                 // USB-specific functions
#include "UsbHid.h"
#include "usbConstructs.h"
#include "hal.h"

// Global flags set by events
volatile uint8_t bHIDDataReceived_event = FALSE;  // Flag set by event handler to 
                                               // indicate data has been 
                                               // received into USB buffer


//*****************************************************************************
//
//! Constructor  
//!
//! \param GPIO port 
//! 	
//! 
//
//*****************************************************************************
USBHumanInterface::USBHumanInterface(uint16_t port)
{

}
//*****************************************************************************
//
//! Sets USB connection  
//!
//! \param None 
//! 	
//! This function sets VCore, initializes Ports, sets up USB connection and
//! enables interrupts.   
//!                                 
//!   
//! \return \b None
//
//*****************************************************************************

void USBHumanInterface::HID_setup(void)
{

	PMM_setVCore(PMM_CORE_LEVEL_2);
	USBHAL_initPorts();

    USB_setup(TRUE, TRUE);                 //Init USB
    __enable_interrupt();                  //Enable interrupts globally

}

//*****************************************************************************
//
//! Checks state of USB connection  
//!
//! \param None 
//! 	
//! This call checks the state of USB. 
//!  ST_ENUM_ACTIVE:  USB is enumerated and active
//!  ST_PHYS_DISCONNECTED: USB is disconnected
//!  ST_ENUM_SUSPENDED: USB enumerated by suspended
//!  ST_PHYS_CONNECTED_NOENUM_SUSP: USB connected but suspended and not 
//!                                 enumerated 
//!  ST_ENUM_IN_PROGRESS:  USB enumeration is in progress
//!                                 
//!  If USB is enumerated and active, the function checks for received data at
//!  the USB buffer and returns a 1.  Else keeps checking for data.
//! 
//! 
//! \return \b 1 - Data received at USB buffer
//
//*****************************************************************************

int USBHumanInterface::HID_start(void)
{

	switch (USB_getConnectionState()) {
	// This case is executed while your device is enumerated on the
    // USB host
    case ST_ENUM_ACTIVE:
	// Sleep if there are no bytes to process.
        __disable_interrupt();
        if (!USBHID_getBytesInUSBBuffer(HID0_INTFNUM)) {
			// Enter LPM0 until awakened by an event handler
			__bis_SR_register(LPM0_bits + GIE);
        }

        __enable_interrupt();
				
		if (bHIDDataReceived_event) {
			bHIDDataReceived_event = FALSE;
			return 1;
		}
				
		break;
    // These cases are executed while your device is disconnected from
    // the host (meaning, not enumerated); enumerated but suspended
    // by the host, or connected to a powered hub without a USB host
    // present. 
	case ST_PHYS_DISCONNECTED:
    case ST_ENUM_SUSPENDED:
    case ST_PHYS_CONNECTED_NOENUM_SUSP:
        __bis_SR_register(LPM3_bits + GIE);
        _NOP();
        break;
    // The default is executed for the momentary state
    // ST_ENUM_IN_PROGRESS.  Usually, this state only last a few
    // seconds.  Be sure not to enter LPM3 in this state; USB
    // communication is taking place here, and therefore the mode must
    // be LPM0 or active-CPU.
	case ST_ENUM_IN_PROGRESS:
	default:;
	}
}

//*****************************************************************************
//
//! Retrieves data that is waiting in the USB buffer. 
//!
//! \param dataBuffer contains bytes of data waiting to be retrieved
//! 	
//! \param buffer_size is the maximum bytes allowed to be received
//!
//! This call only retrieves data that is already waiting in the USB buffer
//! -- that is, data that has already been received by the MCU.  It assumes a
//! previous, open receive operation (began by a direct call to 
//! USBxxx_receiveData()) is NOT under way on this interface; and no receive
//! operation remains open after this call returns.  It doesn't check for 
//! kUSBxxx_busNotAvailable, because it doesn't matter if it's not.  size is the
//! maximum that is allowed to be received before exiting; i.e., it
//! is the size allotted to dataBuf.  Returns the number of bytes received. 
//! 
//! 
//! \return \b count - Number of bytes received
//
//*****************************************************************************

uint16_t USBHumanInterface::HID_receiveDataFromHost(uint8_t *dataBuffer, uint16_t buffer_size)
{
    uint16_t count = 0;
	//Data sent by host via USB and received by launchpad at its IN endpoint
	count = USBHID_receiveDataInBuffer((uint8_t*)dataBuffer, buffer_size, HID0_INTFNUM);
    return count;
}

//*****************************************************************************
//
//! Sends data to Host from USB buffer 
//!
//! \param dataBuffer contains the bytes of data sent to host
//! 	
//! \param count is the number of bytes of data to be sent
//!
//! This construct implements post-call polling to ensure the sending completes
//! before the function returns.  It provides the simplest coding, at the 
//! expense of wasted cycles and potentially allowing MCU execution to become
//! "locked" to the host, a disadvantage if the host (or bus) is slow.  The 
//! function also checks all valid return codes, and returns non-zero if an 
//! error occurred.
//! It assumes no previous send operation is under way; also assumes size is 
//! non-zero.
//! 
//! 
//! \return \b 1 (succeeded) or 0 (error)
//
//*****************************************************************************

uint8_t USBHumanInterface::HID_sendDataToHost(uint8_t *dataBuffer, uint16_t count)
{
    //Data sent by launchpad to its OUT endpoint to be transmitted back to the host
	if(USBHID_sendDataAndWaitTillDone ((uint8_t*)dataBuffer,count,HID0_INTFNUM,1)) 
		return 0;  //error
	else 
		return 1;  //success
}

//*****************************************************************************
//
//! Aborts an Active Send Operation on Data Interface.
//!
//! \param size is the number of bytes that were sent prior to the abort
//! 	action.
//! \param intfNum is the data interface for which the send should be
//! 	aborted.
//!
//! Aborts an active send operation on data interface intfNum. Returns
//! the number of bytes that were sent prior to the abort, in size.
//! 
//! An application may choose to call this function if sending failed, due to
//! factors such as:
//! - a surprise removal of the bus
//! - a USB suspend event
//! - any send operation that extends longer than desired//! 
//! 
//! \return \b 1 (succeeded)
//
//*****************************************************************************
uint8_t USBHumanInterface::HID_abortDataToHost(uint16_t *size, uint8_t intfNum)
{
	USBHID_abortSend (size, intfNum);
    return 1;
}

//*****************************************************************************
//
//! Rejects Data Received from the Host.
//!
//! This function rejects data that has been received from the host, for
//! interface intfNum, that does not have an active receive operation under
//! way. It resides in the USB endpoint buffer and blocks further data until a
//! receive operation is opened, or until rejected. When this function is
//! called, the buffer for this interface is purged, and the data lost. This
//! frees the USB path to resume communication.
//! 
//! See Sec. 7.2 of "Programmer's Guide: MSP430 USB API Stack for 
//! CDC/PHDC/HID/MSC" for a detailed discussion of receive operations.
//!
//! \return \b 1  (succeeded)
//
//*****************************************************************************
uint8_t USBHumanInterface::HID_rejectDataFromHost(uint8_t intfNum)
{
	USBHID_rejectData (intfNum);
	return 1;
}


//*****************************************************************************
//
//! Aborts an Active Receive Operation on HID Interface.
//!
//! \param size is the number of bytes that were received and are waiting at the
//! 	assigned address.
//! \param intfNum is the data interface for which the receive should be
//! 	aborted.
//!
//! Aborts an active receive operation on HID interface intfNum. Returns the
//! number of bytes that were received and transferred to the data location
//! established for this receive operation. The data moved to the buffer up to
//! that time remains valid.
//! 
//! An application may choose to call this function if it decides it no longer
//! wants to receive data from the USB host. It should be noted that if a
//! continuous stream of data is being received from the host, aborting the
//! operation is akin to pressing a "pause" button; the host will be NAK'ed
//! until another receive operation is opened.
//! 
//! See Sec. 7.2 of "Programmer's Guide: MSP430 USB API Stack for 
//! CDC/PHDC/HID/MSC" for a detailed discussion of receive operations.
//!
//! \return \b 1 (succeeded)
//
//*****************************************************************************
uint8_t USBHumanInterface::HID_abortDataFromHost(uint16_t *size, uint8_t intfNum)
{
	USBHID_abortReceive (size, intfNum);
	return 1;
}
/*  
 * ======== UNMI_ISR ========
 */
void __attribute__ ((interrupt(UNMI_VECTOR))) UNMI_ISR (void)
{
  switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG ))
    {
        case SYSUNIV_NONE:
            __no_operation();
            break;
        case SYSUNIV_NMIIFG:
            __no_operation();
            break;
        case SYSUNIV_OFIFG:
            UCS_clearFaultFlag(UCS_XT2OFFG);
            UCS_clearFaultFlag(UCS_DCOFFG);
            SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
            break;
        case SYSUNIV_ACCVIFG:
            __no_operation();
            break;
        case SYSUNIV_BUSIFG:
            // If the CPU accesses USB memory while the USB module is
            // suspended, a "bus error" can occur.  This generates an NMI.  If
            // USB is automatically disconnecting in your software, set a
            // breakpoint here and see if execution hits it.  See the
            // Programmer's Guide for more information.
            SYSBERRIV = 0; //clear bus error flag
            USB_disable(); //Disable
    }

}
