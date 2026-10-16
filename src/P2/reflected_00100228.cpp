// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
int func_0013B500(char *receiver,int kind);
CRef *func_0012B2F0(CRef *,int);
}
extern "C" CRef *func_00100228(CRef *output,char *receiver,int count,CRef *values)
{
    CRef temporary;
    int schema[1]={7};
    int kind;
    func_0024B2B8(&temporary,1,values,schema,&kind);
    func_0012B2F0(&temporary,func_0013B500(receiver,kind)!=0);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
