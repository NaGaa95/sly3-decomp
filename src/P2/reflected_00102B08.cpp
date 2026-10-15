// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
struct S;
struct V { float x,y,z; };
void func_00248E98(S *,V *,float);
}
extern "C" CRef *func_00102B08(CRef *output,void *receiver,int count,CRef *values)
{
    int schema[2]={1,0xB};
    V vector;
    CRef temporary;
    float amount;
    func_0024B2B8(&temporary,2,values,schema,&amount,&vector);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    func_00248E98(static_cast<S *>(receiver),&vector,amount);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
