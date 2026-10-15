// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
struct State;
void func_00131358(State *,int,int,int,float,float,float);
}
extern "C" CRef *func_00101AC0(CRef *output,void *receiver,int count,CRef *values)
{
    int schema[6]={0xE,0x5,0x5,0x1,0x1,0x1};
    CRef temporary;
    int first;
    int second;
    int third;
    float fourth;
    float fifth;
    float sixth;
    func_0024B2B8(&temporary,6,values,schema,&first,&second,&third,&fourth,&fifth,&sixth);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    func_00131358(static_cast<State *>(receiver),first,second,third,fourth,fifth,sixth);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
