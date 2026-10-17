// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "scene.h"
typedef int qword __attribute__((mode(TI)));
struct Anchor { unsigned char prefix[0x14]; float weight; unsigned char gap18[0x28]; qword point; unsigned char gap50[0x10]; };
struct Anchored { unsigned char prefix[0x190]; Anchor anchors[4]; };
extern "C" void func_0023E290(void *object);
extern "C" qword func_001C9428(SCENE_OBJECT *source,SCENE_OBJECT *destination,qword point);
extern "C" void func_0023E940(void *object,qword point,float weight);
extern "C" void func_0027C278(Anchored *object)
{
    unsigned i;
    func_0023E290(object);
    for(i=0;i<4;i++) {
        Anchor *anchor=&object->anchors[i];
        func_0023E940(object,func_001C9428((SCENE_OBJECT *)object,0,anchor->point),anchor->weight);
    }
}
