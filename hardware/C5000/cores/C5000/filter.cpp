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

/** @file filter.cpp
 *
 *  @brief Filter API implementation
 *
 */

#include "filter.h"

void filter_iirSecondOrder(const int length,
                           const int *input,
                           int       *output,
                           const int *coeffs,
                           int       *delayBuf)
{
	register int n;
	register int a_0, a_1, a_2, b_0, b_1, b_2;
	long x_0, x_1, x_2, y_0, y_1, y_2;

	a_0 = (int)coeffs[0];
	a_1 = (int)coeffs[1];
	a_2 = (int)coeffs[2];
	b_0 = (int)coeffs[3];
	b_1 = (int)coeffs[4];
	b_2 = (int)coeffs[5];

    x_1 = (long)delayBuf[0];
    x_2 = (long)delayBuf[1];
    y_1 = (long)delayBuf[2];
    y_2 = (long)delayBuf[3];

	for(n = 0; n < length; n++)
	{
		x_0 = (long)input[n];
		y_0 = (x_0 * b_0 + x_1 * b_1 + x_2 * b_2 - y_1 * a_1 - y_2 * a_2) >> a_0;
        output[n] = (int)y_0;
		x_2 = x_1;
		x_1 = x_0;
		y_2 = y_1;
		y_1 = y_0;
	}

	delayBuf[0] = (int)x_1;
	delayBuf[1] = (int)x_2;
	delayBuf[2] = (int)y_1;
	delayBuf[3] = (int)y_2;
}

void filter_iirArbitraryOrder(int       length,
                              int       *input,
                              int       *output,
                              const int *coeffs,
                              int       *delayBuf,
                              int       order)
{
    register int index;
    register int size;
    const int iirCoeffCount = 6;
    const int iirDelayCount = 4;

    for (index = 0; index < order/2; index++)
    {
    	filter_iirSecondOrder(length, (const int*)input, output,
    	                      &coeffs[(iirCoeffCount*index)],
    	                      &delayBuf[(iirDelayCount*index)]);

    	for (size = 0; size < length; size++)
    	{
    	    input[size] = output[size];
    	}
    }
}

int filter_fir(int          *input,
               int          *coeffs,
               int          *output,
               int          *delayBuffer,
               unsigned int noOfSamples,
               unsigned int noOfCoeffs)
{
    int overFlow;

    overFlow = (int)fir((DATA*)input, (DATA*)coeffs,
                        (DATA*)output, (DATA*)delayBuffer,
                        noOfSamples, noOfCoeffs);

    return (overFlow);
}
