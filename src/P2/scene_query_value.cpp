// Read or update the float value attached to a queried scene object.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"
extern "C" unsigned char D_00475480[];
extern "C" void func_0015B6B0(void *,void *);
extern "C" void func_001C9918(SCENE_OBJECT *object,float value) {
    float *queried=(float *)SceneQuery(object);
    if(queried) {
        *queried=value;
        func_0015B6B0(D_00475480,queried);
    }
}
extern "C" float func_001C9988(SCENE_OBJECT *object) {
    float *queried=(float *)SceneQuery(object);
    float value=-1.0f;
    if(queried)value=*queried;
    return value;
}
