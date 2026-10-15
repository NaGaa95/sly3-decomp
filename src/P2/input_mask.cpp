// Original mask query followed by consumption, for two concrete table layouts.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "input_mask.h"
extern "C" unsigned int func_001A98B8(float threshold,const INPUT_MASK_BUFFERED *input,unsigned int mask) {
    return input->pending30&mask;
}
extern "C" void func_001A98C8(INPUT_MASK_BUFFERED *input,unsigned int mask) {
    input->pending30&=~mask;
}
extern "C" unsigned int func_001A8FB8(float threshold,const INPUT_MASK_TIMED *input,unsigned int mask) {
    unsigned int result=0;
    float now=D_0036BB98.now;
    int i=0;
    unsigned int bit=1;
    for(;i<16;++i,bit<<=1) {
        if(mask&bit) {
            if(now-input->timestamps1070[i]<=threshold)result|=bit;
        }
    }
    return result;
}
extern "C" void func_001A9010(INPUT_MASK_TIMED *input,unsigned int mask) {
    int i=0;
    unsigned int bit=1;
    for(;i<16;++i,bit<<=1) {
        if(mask&bit)input->timestamps1070[i]=D_00322320;
    }
}
