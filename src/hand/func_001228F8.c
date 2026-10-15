// SLY3_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Private measured builtin wrapper ABI: count, CRef array, frame, then operation.
#include "eval_dispatch_api.h"
CRef *func_00122880(CRef *output,int count,CRef *arguments,EvalFrame *frame,int operation);
CRef *func_001228F8(CRef *output,int count,CRef *arguments,EvalFrame *frame)
{
    func_00122880(output,count,arguments,frame,0x23);
    return output;
}
