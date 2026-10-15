// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
CRef *func_0012B270(CRef *,int);
int func_002157C0(void *,int);
}
extern "C" CRef *func_00110BA8(CRef *output,void *receiver,int count,CRef *values)
{
    CRef temporary;
    int schema[1]={0x1082};
    int index;
    func_0024B2B8(&temporary,1,values,schema,&index);
    func_0012B270(&temporary,func_002157C0(receiver,index));
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
