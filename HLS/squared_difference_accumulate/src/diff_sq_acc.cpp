/************************************************
Copyright (c) 2016, Xilinx, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation 
and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors 
may be used to endorse or promote products derived from this software 
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.// Copyright (c) 2016 Xilinx, Inc.
************************************************/

#include "../src/diff_sq_acc.h"

void diff_sq_acc(stream_t* a, stream_t* b, stream_t* dout)
{
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE axis register both port=dout
#pragma HLS INTERFACE axis register both port=b
#pragma HLS INTERFACE axis register both port=a
	int i;
	int acc= 0;
	int a_reg1, b_reg1, sub, sub2;
	value_t valTemp1;
	value_t valTemp2;
	for(i=0; i<N; i++)
	{
		#pragma HLS PIPELINE II=1
		valTemp1  = a->read();
		valTemp2  = b->read();
		a_reg1=valTemp1.data;
		b_reg1=valTemp2.data;
		sub = a_reg1 - b_reg1;
		sub2 = sub*sub;
		acc += sub2;
	}
	valTemp1.data = acc;
	valTemp1.keep = 0xF;
	valTemp1.strb = 0;
	valTemp1.user = 0;
	valTemp1.last = 1;
	valTemp1.id = 0;
	valTemp1.dest = 0;
	dout->write(valTemp1);
}

