// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
struct P;
void func_00241890(P *,float,float);
}
extern "C" CRef *func_00101448(CRef *output,void *receiver,int count,CRef *values)
{
    int schema[2]={1,1};
    CRef temporary;
    float first;
    float second;
    func_0024B2B8(&temporary,2,values,schema,&first,&second);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    func_00241890(static_cast<P *>(receiver),first,second);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
