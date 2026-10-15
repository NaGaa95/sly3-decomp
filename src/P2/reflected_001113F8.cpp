// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
struct S;
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
void func_00219420(S *,qword);
}
extern "C" CRef *func_001113F8(CRef *output,void *receiver,int count,CRef *values)
{
    qword pair[1];
    CRef temporary;
    int schema[1]={0x2};
    func_0024B2B8(&temporary,1,values,schema,&pair[0]);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    func_00219420(static_cast<S *>(receiver),pair[0]);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
