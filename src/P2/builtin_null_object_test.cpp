// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}

extern "C" CRef *func_00122638(CRef *output, int count,
                               CRef *arguments, EvalFrame *frame)
{
    int result = arguments[0].tag == 0x1F && arguments[0].payload.pointer == 0;
    output->tag = 0x15;
    output->payload.integer = result;
    return output;
}
