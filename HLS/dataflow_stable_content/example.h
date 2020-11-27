
#include <ap_axi_sdata.h>
#include <hls_stream.h>


#define MAP_ALIGN_4INT			(((N + 3) >> 2) << 2)

typedef ap_axiu<32,1,1,1> value_t;
typedef hls::stream<value_t> strm_t;
typedef ap_uint<32> reg32_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
