// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
#include "mat.h"
struct SceneLightingPayload { char bytes[48]; };
struct SceneTransformState {
    SCENE_OBJECT scene;
    char pad68[8];
    char methodState[0x9C];
    SceneLightingPayload *fallback;
};
extern "C" char D_00475480[];
extern "C" void func_001C6418(void *,MATRIX4 *,SceneLightingPayload *);
extern "C" void func_0018E800(void *,qword,MATRIX4 *,float,float,SceneLightingPayload *);
extern "C" void func_002BE8D0(void *,int);
struct SceneTransformScope {
    ~SceneTransformScope() { func_002BE8D0(this,2); }
};
typedef void (*SceneTransformBody)(void *,qword,MATRIX4 *,float,float,SceneLightingPayload *);
typedef char CheckScenePrefix68[sizeof(SCENE_OBJECT)==0x68?1:-1];
typedef char CheckPayload48[sizeof(SceneLightingPayload)==48?1:-1];
typedef char CheckScope1[sizeof(SceneTransformScope)==1?1:-1];
extern "C" void func_0023CCB0(SceneTransformState *object,qword value,MATRIX4 *matrix,float first,float second,SceneLightingPayload *payload) {
    SceneLightingPayload local;
    SceneTransformScope scope;
    if (!payload && object->fallback) {
        local=*object->fallback;
        payload=&local;
        func_001C6418(D_00475480,matrix,&local);
    }
    func_0018E800(object->methodState,value,matrix,first,second,payload);
    for(SCENE_OBJECT *child=object->scene.children.first;child!=object->scene.anchor;child=child->previous) {
        SCENE_VIRTUAL_ENTRY *entry=&child->vtable[22];
        ((SceneTransformBody)entry->Simple)((char *)child+entry->delta,value,matrix,first,second,payload);
    }
}
