// Controller analog values, script gates, and callback forwarding.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "input_table.h"
extern "C" float func_001A90D8(const INPUT_TABLE_ANALOG_VIEW *input,unsigned int index) {
    if(input->base.held18&D_00345128[index]) {
        if(input->inputVersion1054>=4) {
            int value=input->values1118[index];
            int minimum=1;
            if(minimum<value)minimum=value;
            return minimum*(1.0f/255.0f);
        }
        return 1.0f;
    }
    return 0.0f;
}


extern "C" int func_001A7C58(const INPUT_STATE_BASE_VIEW *,unsigned int) { return 0; }
extern "C" int func_001A7C60(const INPUT_STATE_BASE_VIEW *,unsigned int) { return 0; }
extern "C" void func_001A9098(float value,INPUT_TABLE_CALLBACK_VIEW *input,const INPUT_TABLE_CALLBACK_DESCRIPTOR *descriptor) {
    if(input->inputVersion1054>=3&&input->mode1050==3)
        func_00210C08(value,(INPUT_TABLE_CALLBACK_STATE *)input->callback1124,descriptor);
}
