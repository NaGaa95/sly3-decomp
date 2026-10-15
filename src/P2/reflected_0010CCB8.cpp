// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
}
/* Only offsets E4/E8 are established; these are raw32 machine words. */
struct ReflectedRawPairPrefix { char unknown[0xE4]; int first; int second; };
extern "C" CRef *func_0010CCB8(CRef *output,ReflectedRawPairPrefix *receiver,int count,CRef *values)
{
    int schema[2]={0x2002,0x2005};
    CRef temporary;
    int first;
    int second;
    func_0024B2B8(&temporary,2,values,schema,&first,&second);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    receiver->first=first;
    receiver->second=second;
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
