// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct SceneScalarState {
    SCENE_OBJECT scene;
    char pad68[0x118-0x68];int queryGeneration;
};
extern "C" unsigned char D_00475480[];
extern "C" void func_00211F18(void *);
extern "C" void func_00211F90(void *);
extern "C" void func_0015ADA0(void *,SCENE_HANDLE *);
extern "C" void func_002BE8D0(void *,int);
struct SceneScalarScope { ~SceneScalarScope() { func_002BE8D0(this,2); } };
typedef char CheckSceneScalarScope1[sizeof(SceneScalarScope)==1?1:-1];
typedef void (*SceneScalarMethod)(void *,float);
extern "C" void func_0023BFE8(SceneScalarState *object,float value) {
    SceneScalarScope scope;
    object->scene.time34=value;
    if(object->queryGeneration!=-1) {
        func_00211F18(object);
        func_00211F90(object);
    }
    if(!object->scene.owner) {
        int inherited=object->scene.flags.fields.inherited;
        if(inherited) func_0015ADA0(D_00475480,object->scene.handle);
    }
    for(SCENE_OBJECT *child=object->scene.children.first;child;child=child->previous) {
        if(value<child->time34) {
            SCENE_VIRTUAL_ENTRY *entry=&child->vtable[46];
            ((SceneScalarMethod)entry->Simple)((char *)child+entry->delta,value);
        }
    }
}
