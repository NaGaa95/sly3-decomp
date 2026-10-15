// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct State;
struct PairWords { int first,second; };
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
void func_001FD460(State *,const PairWords *);
}
extern "C" CRef *func_00107820(CRef *output,void *receiver,int count,CRef *values)
{
    PairWords pair;
    CRef temporary;
    int schema[1]={0xA};
    func_0024B2B8(&temporary,1,values,schema,&pair);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    func_001FD460(static_cast<State *>(receiver),&pair);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
