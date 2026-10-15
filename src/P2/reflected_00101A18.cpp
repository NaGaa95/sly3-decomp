// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);


}
struct SCROLLER;
void SetScrollerMasterSpeeds(SCROLLER *,float,float) __asm__("func_00237DD8");
extern "C" CRef *func_00101A18(CRef *output,void *receiver,int count,CRef *values)
{
    int schema[2]={1,1};
    CRef temporary;
    float first;
    float second;
    func_0024B2B8(&temporary,2,values,schema,&first,&second);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    SetScrollerMasterSpeeds(static_cast<SCROLLER *>(receiver),first,second);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
