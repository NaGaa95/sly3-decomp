// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
CRef *func_0012B2F0(CRef *,int);

int func_001985F0(char *,void *);
}
extern "C" CRef *func_00104820(CRef *output,void *receiver,int count,CRef *values)
{
    CRef temporary;
    int schema[1]={0x2086};
    int value;
    func_0024B2B8(&temporary,1,values,schema,&value);
    func_0012B2F0(&temporary,func_001985F0(static_cast<char *>(receiver),reinterpret_cast<void *>(value)) != 0);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
