// Controller query followed by consumption through the original virtual ABI.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "input_interface.h"
#include "input_query_api.h"
extern "C" unsigned int func_001A7A80(void *receiver,unsigned int mask,float threshold) {
    INPUT_INTERFACE *input=(INPUT_INTERFACE *)receiver;
    unsigned int result=input->Query(threshold,mask);
    input->Consume(result);
    return result;
}
extern "C" int func_001A7AE0(INPUT_INTERFACE *input,unsigned int required,unsigned int excluded) {
    unsigned int held=input->held18&(required|excluded);
    int result=0;
    if(held==required)result=func_001A7A80(input,held,0.0f)!=0;
    return result;
}
