// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "mat.h"
extern "C" {
#include "eval_dispatch_api.h"
void func_0011D830(void *first,MATRIX4 *second,MATRIX4 *output);
}

extern "C" CRef *func_00124BF0(CRef *output,int count,CRef *arguments,EvalFrame *frame)
{
    CRef temporary;
    func_0012BDD8(&temporary,0x19);
    func_0011D830(arguments[0].payload.pointer,
                 static_cast<MATRIX4 *>(arguments[1].payload.pointer),
                 static_cast<MATRIX4 *>(temporary.payload.pointer));
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
