// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "scene.h"
extern "C" char D_0036BB98[];
extern "C" void func_00165548(void *clock,int channel,float scale);
extern "C" void func_002263B0(SCENE_OBJECT *object,float scale)
{
    func_00165548(D_0036BB98,6,scale);
    if(scale==0.0f) {
        int tagged=object->field3C;
        if((tagged^1)&1) *(int *)tagged|=0x200;
        else object->field3C=tagged|0x200;
    } else {
        int tagged=object->field3C;
        if((tagged^1)&1) *(int *)tagged&=~0x200;
        else object->field3C=tagged&~0x200;
    }
}
