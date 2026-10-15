// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
struct S;
void func_002427E0(S *,int,qword,float,float,float,float);
}
extern "C" CRef *func_0010DA20(CRef *output,void *receiver,int count,CRef *values)
{
    int schema[6]={0x5,0x1,0x1,0x1,0x1,0x2};
    qword sixth[1];
    CRef temporary;
    int first;
    float second;
    float third;
    float fourth;
    float fifth;
    func_0024B2B8(&temporary,6,values,schema,&first,&second,&third,&fourth,&fifth,&sixth[0]);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    func_002427E0(static_cast<S *>(receiver),first,sixth[0],second,third,fourth,fifth);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
