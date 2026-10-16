// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
extern float D_0031F4D4;
}

extern "C" CRef *func_00124228(CRef *output, int count,
                               CRef *arguments, EvalFrame *frame)
{
    float value = D_0031F4D4;
    output->tag = 0x14;
    output->payload.real = value;
    return output;
}
