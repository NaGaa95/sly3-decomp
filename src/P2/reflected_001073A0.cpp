// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
struct O;
CRef *func_0012B768(CRef *,O *);
void *func_001FE728(void *receiver,int flags);
}
extern "C" CRef *func_001073A0(CRef *output,void *receiver,int count,CRef *values)
{
    CRef temporary;
    func_0024B2B8(&temporary,0,values,0);
    func_0012B768(&temporary,static_cast<O *>(func_001FE728(receiver,1)));
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
