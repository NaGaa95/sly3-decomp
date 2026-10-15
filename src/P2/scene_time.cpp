// Update scene time and refresh a root object's world scheduling entry.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"
extern "C" unsigned char D_00475480[];
extern "C" void func_0015ADA0(void *,SCENE_HANDLE *);
extern "C" void func_001C90B0(SCENE_OBJECT *object,float time) {
    object->time34=time;
    int inherited=object->flags.fields.inherited;
    if(inherited&&!object->owner)func_0015ADA0(D_00475480,object->handle);
}
extern "C" int func_001C9100(SCENE_OBJECT *object) {
    return object->flags.fields.state48;
}
