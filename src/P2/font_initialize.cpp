// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "range_context_api.h"
struct FONT;
struct FD;
extern "C" {
extern char D_0036BF10[],D_0036C2D0[];
extern int D_0036DBFC;
extern FD *D_00344FA0[3];
void *func_00292034(void *,int,unsigned int);
void func_00181118(FONT *,FD *,void *);
}
extern "C" void func_001807A0(void)
{
    func_00292034(D_0036BF10,0,0x3C0);
    func_00292034(D_0036C2D0,0,12);
    ZPR context;
    int rangeUnit=D_0036DBFC;
    func_00196AA8(&context,rangeUnit*2,rangeUnit*3);
    for(int i=0;i<3;++i) {
        FONT *font=reinterpret_cast<FONT *>(D_0036BF10+i*0x140);
        FD *data=D_00344FA0[i];
        if(data)
            func_00181118(font,data,&context);
    }
}
