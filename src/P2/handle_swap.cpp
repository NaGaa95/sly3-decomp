// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
extern "C" int func_00165DC8(void *object);
extern "C" void func_0025EA08(void *holder,SCENE_OBJECT *object,SCENE_OBJECT **slot)
{
    SCENE_OBJECT *previous=*slot;
    int released=0;
    if(previous) {
        if(!func_00165DC8(previous)) {
            released=1;
            CallScene(previous,57);
        }
    }
    *slot=object;
    if(object&&released)
        CallScene(object,56);
}
