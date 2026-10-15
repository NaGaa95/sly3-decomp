// Recovered scene handle and queried-resource registration checks.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"
extern "C" SCENE_LIST D_00479278,D_00479310;
extern "C" int func_0011B0C0(SCENE_LIST *,void *);
extern "C" int func_001C8610(SCENE_OBJECT *object) {
    int found=0;
    int inherited=object->flags.fields.inherited;
    if(inherited)found=func_0011B0C0(&D_00479278,object->handle)!=0;
    return found;
}
extern "C" int func_001C8658(SCENE_OBJECT *object) {
    void *value=SceneQuery(object);
    int result;
    if(!value)result=0;
    else result=func_0011B0C0(&D_00479310,value);
    return result;
}
