// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
struct State;
void func_001FD390(State *,int,float,float,float,float);
}
extern "C" CRef *func_001076C8(CRef *output,void *receiver,int count,CRef *values)
{
    int schema[5]={0xE,0x1,0x1,0x1,0x1};
    CRef temporary;
    int first;
    float second;
    float third;
    float fourth;
    float fifth;
    func_0024B2B8(&temporary,5,values,schema,&first,&second,&third,&fourth,&fifth);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    func_001FD390(static_cast<State *>(receiver),first,second,third,fourth,fifth);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
