// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
void func_001974E8(void *);
}
extern "C" CRef *func_001085C8(CRef *output,void *receiver,int count,CRef *values)
{
    CRef temporary;
    func_0024B2B8(&temporary,0,values,0);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    func_001974E8(receiver);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
