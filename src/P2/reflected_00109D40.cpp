// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
CRef *func_0012B270(CRef *,int);
int func_001C21D0(void *rows,int index);
}
extern "C" CRef *func_00109D40(CRef *output,void *receiver,int count,CRef *values)
{
    CRef temporary;
    int schema[1]={0x1087};
    int index;
    func_0024B2B8(&temporary,1,values,schema,&index);
    func_0012B270(&temporary,func_001C21D0((char *)receiver+0xE40,index));
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
