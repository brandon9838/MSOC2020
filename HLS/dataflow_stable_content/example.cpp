// 67d7842dbbe25473c3c32b93c0da8047785f30d78e8a024de1b57352245f9689
#include "example.h"




void example(strm_t &in1_strm, strm_t &in2_strm, strm_t &out_strm)
{
#pragma HLS INTERFACE axis register both port=out_strm
#pragma HLS INTERFACE axis register both port=in2_strm
#pragma HLS INTERFACE axis register both port=in1_strm
#pragma HLS INTERFACE s_axilite port=return
    // tb is read twice in "readmem"
    int tb[10];
#pragma HLS RESOURCE variable=tb core=RAM_2P_BRAM
    //#pragma HLS RESOURCE core = RAM_2P_BRAM variable = tb
    load:
        for (int i = 0; i < 10; i++)
        {
    		#pragma HLS PIPELINE
            int in = in1_strm.read().data;
            if (in<10){
            	tb[i] = in;
            }
            else{
            	tb[i] = 0;
            }
        }
    int sum = 0;
    B:
        for (int i = 0; i < 10; i++)
        {
    		#pragma HLS PIPELINE
            int r = in2_strm.read().data;
            if (r != 0)
            {
                int b = tb[r];
                sum += b;
            }
        }
        value_t valTemp;
        valTemp.data=sum;
        valTemp.keep = 0xF;
        valTemp.strb = 0;
        valTemp.user = 0;
        valTemp.id = 0;
        valTemp.dest = 0;
        valTemp.last=1;
        out_strm.write(valTemp);
    return;
}
