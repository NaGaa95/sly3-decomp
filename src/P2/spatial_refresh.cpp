// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct SpatialRefreshGeneration { unsigned char prefix[0xA4]; int generation; };
struct SpatialRefreshView {
    unsigned char prefix[0x50]; SpatialRefreshGeneration *source;
    unsigned char gap54[0x118-0x54]; int generation;
};
extern "C" unsigned char D_00475480[];
extern "C" void func_00211F18(void *);
extern "C" void func_00211F90(void *);
extern "C" void func_0015ADA0(void *,SCENE_HANDLE *);
extern "C" void func_0015B6B0(void *,void *);
extern "C" void func_0028E6A8(void *receiver)
{
    SCENE_OBJECT *object=(SCENE_OBJECT *)receiver;
    SpatialRefreshView *state=(SpatialRefreshView *)receiver;
    int inherited=object->flags.fields.inherited;
    if(inherited) {
        int generation=state->generation;
        if(generation!=-1 && state->source->generation!=generation) {
            func_00211F18(object);
            func_00211F90(object);
        }
        if(!object->owner)
            func_0015ADA0(D_00475480,object->handle);
        void *value=SceneQuery(object);
        if(value)
            func_0015B6B0(D_00475480,value);
    }
}
