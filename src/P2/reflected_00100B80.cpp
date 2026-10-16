// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
}
struct LOUnaryMethod { short delta; short padding; void (*call)(void *); };
struct LOUsedPrimary { unsigned char unused[72]; LOUnaryMethod method; };
struct LOPrimaryPrefix { unsigned char unused[12]; LOUsedPrimary *primary; };
typedef char CheckLOUnary8[(sizeof(LOUnaryMethod)==8)?1:-1];
extern "C" CRef *func_00100B80(CRef *output,void *receiver,int count,CRef *values)
{
    CRef temporary;
    func_0024B2B8(&temporary,0,values,0);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    LOUnaryMethod &method=((LOPrimaryPrefix *)receiver)->primary->method;
    method.call((char *)receiver+method.delta);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
