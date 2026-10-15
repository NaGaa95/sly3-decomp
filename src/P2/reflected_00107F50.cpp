// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct K { int a,b; };
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
void func_001972F8(void *,K *);
}
extern "C" CRef *func_00107F50(CRef *output,void *receiver,int count,CRef *values)
{
    K pair;
    CRef temporary;
    int schema[1]={0xA};
    func_0024B2B8(&temporary,1,values,schema,&pair);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    func_001972F8(receiver,&pair);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
