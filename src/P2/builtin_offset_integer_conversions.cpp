// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}

extern "C" CRef *func_001255E0(CRef *output, int count,
                               CRef *arguments, EvalFrame *frame)
{
    float value = arguments[0].payload.real;
    output->tag = 0x13;
    output->payload.integer = (int)(value + 1.0f);
    return output;
}

extern "C" CRef *func_00125608(CRef *output, int count,
                               CRef *arguments, EvalFrame *frame)
{
    float value = arguments[0].payload.real;
    output->tag = 0x13;
    output->payload.integer = (int)(value + 0.5f);
    return output;
}
