// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
struct O;
CRef *func_0012B768(CRef *,O *);
struct L;
void *func_002387A8(L *,int);
}
extern "C" CRef *func_00103438(CRef *output,void *receiver,int count,CRef *values)
{
    CRef temporary;
    int schema[1]={0x7};
    int value;
    func_0024B2B8(&temporary,1,values,schema,&value);
    func_0012B768(&temporary,static_cast<O *>(func_002387A8((L *)((char *)receiver+0x29C),value)));
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
