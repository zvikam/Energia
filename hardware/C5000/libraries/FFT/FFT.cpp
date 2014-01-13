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
/** @file FFT.cpp
 *
 *  @brief FFT implementation
 *
 */
 
#include <stdio.h>
#include "FFT.h"

/**
 * Class identifier declaration
 */
FFTClass FFTransform;

/** ===========================================================================
 *   @n@b FFT
 *
 *   @b Description
 *   @n Performs FFT on the given signal.
 *
 *   @b Arguments
 *   @verbatim
 *       Input      <- Input signal buffer pointer
 *       lengthFFT  <- FFT length
 *                     (between 8 and 1024 for CFFT and
 *                     between 16 to 2048 for RFFT)
 *      scaleType   <- Scaling requirement
 *      realComplex <- indicates whether input is real or complex
 *      dataType    <- indicates whether input is of 16bits or 32 bits
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li      FFT_BAD_PARAMS <- Input parameters are not valid
 *   @li      FFT_SUCCESS    <- FFT is success
 *
 *  ===========================================================================
 */
int FFTClass::FFT(void *Input, unsigned short lengthFFT, unsigned short scaleType, unsigned short realComplex, unsigned short dataType)
{
    if(Input != NULL)
	{
        if(realComplex == FFT_REAL)
		{
		    if(dataType == FFTQ15)
			{
                if(scaleType == ENABLE_SCALE)
				{
			        /* perform FFT */
			        rfft((DATA *)Input, lengthFFT, SCALE);
				}
				else if(scaleType == DISABLE_SCALE)
				{
			        /* perform FFT */
			        rfft((DATA *)Input, lengthFFT, NOSCALE);
				}
			}
			else if(dataType == FFTQ31)
			{
                if(scaleType == ENABLE_SCALE)
				{
				    /* perform FFT */
				    rfft32((LDATA *)Input, lengthFFT, SCALE);
				}
                else if(scaleType == DISABLE_SCALE)
				{
				    /* perform FFT */
				    rfft32((LDATA *)Input, lengthFFT, NOSCALE);
				}
			}
			else
			{
			    return FFT_BAD_PARAMS;
			}
		}
		else if(realComplex == FFT_COMPLEX)
		{
            if(dataType == FFTQ15)
			{
                if(scaleType == ENABLE_SCALE)
				{
				    /* perform FFT */
		            cfft((DATA *)Input, lengthFFT, SCALE);
				}
                else if(scaleType == DISABLE_SCALE)
				{
				    /* perform FFT */
		            cfft((DATA *)Input, lengthFFT, NOSCALE);
				}
				/* Bit reversing the output */
	            cbrev((DATA *)Input, (DATA *)Input, lengthFFT);
			}
			else if(dataType == FFTQ31)
			{
                if(scaleType == ENABLE_SCALE)
				{
			        /* perform FFT */
	                cfft32_SCALE((LDATA *)Input, lengthFFT);
				}
				else if(scaleType == DISABLE_SCALE)
				{
			        /* perform FFT */
	                cfft32_NOSCALE((LDATA *)Input, lengthFFT);
				}
				else
				{
				    return FFT_BAD_PARAMS;
				}
				/* Bit reversing the output */
	            cbrev32((LDATA *)Input, (LDATA *)Input, lengthFFT);
			}
			else
			{
			    return FFT_BAD_PARAMS;
			}
		}
		else
		{
		    return FFT_BAD_PARAMS;
		}
	}
	else
	{
	    this->handleErrors();
		return FFT_BAD_PARAMS;
	}

	return FFT_SUCCESS;
}

/** ===========================================================================
 *   @n@b IFFT
 *
 *   @b Description
 *   @n Performs IFFT on the given signal.
 *
 *   @b Arguments
 *   @verbatim
 *       Input       <- Input signal buffer pointer
 *       lengthIFFT  <- IFFT length
 *                      (between 8 and 1024 for CIFFT and
 *                      between 16 to 2048 for RIFFT)
 *      scaleType    <- Scaling requirement
 *      realComplex  <- indicates whether input is real or complex
 *      dataType     <- indicates whether input is of 16bits or 32 bits
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li      FFT_BAD_PARAMS <- Input parameters are not valid
 *   @li      FFT_SUCCESS    <- IFFT is success
 *
 *  ===========================================================================
 */
int FFTClass::IFFT(void *Input, unsigned short lengthIFFT, unsigned short scaleType, unsigned short realComplex, unsigned short dataType)
{
    if(Input != NULL)
	{
        if(realComplex == FFT_REAL)
		{
		    if(dataType == FFTQ15)
			{
                if(scaleType == ENABLE_SCALE)
				{
				    /* perform FFT */
				    rifft((DATA *)Input, lengthIFFT, SCALE);
				}
                else if(scaleType == DISABLE_SCALE)
				{
				    /* perform FFT */
				    rifft((DATA *)Input, lengthIFFT, NOSCALE);
				}
			}
			else if(dataType == FFTQ31)
			{
                if(scaleType == ENABLE_SCALE)
				{
				    /* perform FFT */
				    rifft32((LDATA *)Input, lengthIFFT, SCALE);
				}
                else if(scaleType == DISABLE_SCALE)
				{
				    /* perform FFT */
				    rifft32((LDATA *)Input, lengthIFFT, NOSCALE);
				}
			}
			else
			{
			    return FFT_BAD_PARAMS;
			}
		}
		else if(realComplex == FFT_COMPLEX)
		{
            if(dataType == FFTQ15)
			{
                if(scaleType == ENABLE_SCALE)
				{
				    /* perform FFT */
		            cifft((DATA *)Input, lengthIFFT, SCALE);
				}
				else if(scaleType == DISABLE_SCALE)
				{
				    /* perform FFT */
		            cifft((DATA *)Input, lengthIFFT, NOSCALE);
				}
				/* Bit reversing the output */
	            cbrev((DATA *)Input, (DATA *)Input, lengthIFFT);
			}
			else if(dataType == FFTQ31)
			{
                if(scaleType == ENABLE_SCALE)
				{
			        /* perform FFT */
	                cifft32_SCALE((LDATA *)Input, lengthIFFT);
				}
				else if(scaleType == DISABLE_SCALE)
				{
			        /* perform FFT */
	                cifft32_NOSCALE((LDATA *)Input, lengthIFFT);
				}
				else
				{
				    return FFT_BAD_PARAMS;
				}
				/* Bit reversing the output */
	            cbrev32((LDATA *)Input, (LDATA *)Input, lengthIFFT);
			}
			else
			{
			    return FFT_BAD_PARAMS;
			}
		}
		else
		{
		    return FFT_BAD_PARAMS;
		}
	}
	else
	{
	    this->handleErrors();
		return FFT_BAD_PARAMS;
	}

	return FFT_SUCCESS;
}

/** ===========================================================================
 *   @n@b filter
 *
 *   @b Description
 *   @n Performs filter operation by calculating complex multiplication on
 *      frequency domain inputs.
 *
 *   @b Arguments
 *   @verbatim
 *       long *Input   <- Input signal buffer pointer
 *       long *Taps    <- Filter coefficients buffer pointer
 *       long *Output  <- Output buffer pointer
 *       unsigned short size    <- Size of the buffer
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void FFTClass::filter(long *Input, long *Taps, long *Output, unsigned short size)
{
    int input1Real;
    int input1Img;
    int input2Real;
    int input2Img;
    long outputImg32;
	long outputReal32;
    int outputImg16;
	int outputReal16;
	unsigned short index;

    if((Input != NULL) && (Taps != NULL) && (Output != NULL))
	{
	    // Convolution in Time domain = Multiplication in Frequency Domain
	    // Vector multiply Complex Real and Imag
		for (index = 0; index < size; index++)
		{
			/* Mask data for real and imag data = (real:imag) */
			input1Real   = (int)(Input[index] >> CONVERT_32_TO_16_SHIFT);
			input1Img    = (int)(Input[index] & CONVERT_32_TO_16_MASK);
			input2Real   = (int)(Taps[index] >> CONVERT_32_TO_16_SHIFT);
			input2Img    = (int)(Taps[index] & CONVERT_32_TO_16_MASK);

			/* Calculate complex product to get 32 bit result */
			outputImg32    = ((long)input1Real * input2Img) + ((long)input1Img * input2Real);
			outputReal32   = ((long)input1Real * input2Real) - ((long)input1Img * input2Img);

			/* Convert the product back to 16 bits */
			outputImg16  = (int)(outputImg32 >> Q15_MULT_SHIFT);
			outputReal16 = (int)(outputReal32 >> Q15_MULT_SHIFT);

			/* Pack the output in the form of real and imag data (real:imag) */
			Output[index]    = (((long)outputReal16 & CONVERT_32_TO_16_MASK)<< CONVERT_32_TO_16_SHIFT);
			Output[index]    = Output[index] | ((long)outputImg16 & CONVERT_32_TO_16_MASK);
		}
	}
	else
	{
	    this->handleErrors();
	}
}

/**
 *  buff_copy32
 *
 *  API to copy 32 bit data from input buffer to output buffer
 *
 *  long *input       <-- Input buffer pointer
 *  long *output      <-- Output buffer pointer
 *  long size         <-- Size of the buffer to be copied
 */
void FFTClass::buff_copy32(long *input, long *output, long size)
{
	int count;

	for(count =0; count < size; count++)
	{
		*(output + count) = *(input + count);
	}
}

/**
 *
 *  handleErrors(int status)
 *
 *      Handle errors returned by the APIs.
 *
 */
void FFTClass::handleErrors(void)
{

}
