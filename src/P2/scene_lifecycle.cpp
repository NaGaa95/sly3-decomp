// Recovered scene handle release, reverse callbacks and deferred timed queue.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"
struct SCENE_QUEUE {
    char prefix[0x3BE4];int count;SCENE_OBJECT *objects[64];float times[64];
};
extern "C" SCENE_QUEUE D_00475480;
extern "C" float D_0036BB98;
extern "C" void func_0015AD18(SCENE_QUEUE *,SCENE_HANDLE *);
extern "C" void func_0011E1F0(void *,void *);
extern "C" void func_001C74B0(SCENE_OBJECT *object) {
    func_0015AD18(&D_00475480,object->handle);
    func_0011E1F0((char *)&D_00475480+0x3BCC,object->handle);
    object->handle=0;
}
extern "C" void func_001C7FA8(SCENE_OBJECT *object,float time) {
    if(time<=D_0036BB98) {
        object->flags.fields.pending=1;
        return;
    }
    int index;
    if(object->flags.fields.queued) {
        for(index=0;index<D_00475480.count;index++)
            if(object==D_00475480.objects[index])break;
    } else {
        if((unsigned int)D_00475480.count<64) {
            index=D_00475480.count++;
            D_00475480.objects[index]=object;
            object->flags.fields.queued=1;
        } else return;
    }
    if(index<D_00475480.count) {
        D_00475480.times[index]=time;
        object->flags.fields.pending=0;
    }
}
