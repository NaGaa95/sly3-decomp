// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}

extern "C" CRef *func_001224C8(CRef *output, int count,
                               CRef *arguments, EvalFrame *frame)
{
    int tag = arguments[0].tag;
    output->tag = 0x15;
    output->payload.integer = tag == 0x14;
    return output;
}

extern "C" CRef *func_001224E8(CRef *output, int count,
                               CRef *arguments, EvalFrame *frame)
{
    int tag = arguments[0].tag;
    output->tag = 0x15;
    output->payload.integer = tag == 0x13;
    return output;
}
