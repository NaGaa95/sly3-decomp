// Transition timestamps, selected-input routing and digital axis values.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "input_state_more.h"
extern "C" int func_00156700(const INPUT_STATE_OWNER_VIEW *);
extern "C" void func_001A9880(INPUT_STATE_OWNER_VIEW *owner,void *provided) {
    owner->provided1440=provided;
    void *selected;
    if(func_00156700(owner))selected=&owner->buffered140C;
    else selected=owner->provided1440;
    owner->selected134=selected;
}
extern "C" float func_001A98E0(const INPUT_STATE_BASE_VIEW *input,unsigned int index) {
    return (input->held18&D_00345128[index])?1.0f:0.0f;
}
extern "C" void func_001A8F10(INPUT_STATE_TIMED_VIEW *input) {
    unsigned int held=input->base.held18;
    float now=D_0036BB98.now;
    int i=0;
    unsigned int bit=1;
    for(;i<16;++i,bit<<=1) {
        if(held&bit) {
            if(!(input->previousMask1068&bit))input->timestamps1070[i]=now;
        }
    }
    input->base.leftStateTimes1C[input->base.leftAmount>0.0f]=now;
    input->base.rightStateTimes24[input->base.rightAmount>0.0f]=now;
}
