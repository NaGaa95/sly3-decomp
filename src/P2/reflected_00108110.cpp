// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
void *func_00197388(void *,void *,float);
}
extern "C" CRef *func_00108110(CRef *output,void *receiver,int count,CRef *values)
{
    int schema[2]={0x1, 0x6};
    CRef temporary;
    float real;
    int integer;
    func_0024B2B8(&temporary,2,values,schema,&real,&integer);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    func_00197388(receiver,reinterpret_cast<void *>(integer),real);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
