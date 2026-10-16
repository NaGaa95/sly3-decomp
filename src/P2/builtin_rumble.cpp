// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
extern "C" unsigned char D_0036E740[];
extern "C" CRef *func_0012BAE8(CRef *,CRef *);
extern "C" void func_001A9058(char *controller,int kind,float duration);
extern "C" CRef *func_00127158(CRef *output,int count,CRef *arguments,EvalFrame *frame)
{
    int channel;
    switch(count) {
    case 2:channel=0;break;
    case 3:channel=((ScriptNode *)arguments[2].payload.pointer)->ref.payload.integer;break;
    }
    if(channel!=-1) {
        char *controller=(char *)D_0036E740+channel*0x11C0;
        int kind=arguments[0].payload.integer;
        CRef duration;
        func_0012BAE8(&duration,arguments+1);
        func_001A9058(controller,kind,duration.payload.real);
        func_0012BC20(&duration);
    }
    CRef result;
    func_0012BDD8(&result,0x22);
    func_0012AF00(output,&result);
    func_0012BC20(&result);
    return output;
}
