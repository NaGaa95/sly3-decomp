// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
struct LO;
void func_0013B640(LO *,int,float);
}
extern "C" CRef *func_001003F8(CRef *output,void *receiver,int count,CRef *values)
{
    int schema[2]={0x15, 0x1};
    CRef temporary;
    int integer;
    float real;
    func_0024B2B8(&temporary,2,values,schema,&integer,&real);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    func_0013B640(static_cast<LO *>(receiver),integer,real);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
