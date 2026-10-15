// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct SceneParentState {
    SCENE_OBJECT scene;
    char pad68[0xD0-0x68];
    int recordCount;
    void *records;
};
extern "C" void func_001C7CC8(SCENE_OBJECT *,SCENE_OBJECT *,int);
extern "C" void func_0028E768(void *);
extern "C" void func_0023BA40(void *);
extern "C" void func_0023B9C8(void *);
extern "C" void func_002BE8D0(void *,int);
struct SceneParentScope { ~SceneParentScope() { func_002BE8D0(this,2); } };
typedef char CheckParentScope1[sizeof(SceneParentScope)==1?1:-1];
typedef char CheckParentD8[sizeof(SceneParentState)==0xD8?1:-1];
static inline SCENE_OBJECT *FindDetachedOwner(SCENE_OBJECT *object) {
    while(object && !(object->flags.value&(1UL<<52))) object=object->owner;
    return object;
}
extern "C" void func_0023BD00(SceneParentState *object,SCENE_OBJECT *changedRoot,SCENE_OBJECT *previousOwner) {
    SceneParentScope scope;
    func_001C7CC8(&object->scene,changedRoot,(int)previousOwner);
    func_0028E768(object);
    SCENE_OBJECT *current;
    for(current=object->scene.children.first;current;current=current->previous) {
        SCENE_VIRTUAL_ENTRY *entry=&current->vtable[13];
        entry->Parent((char *)current+entry->delta,changedRoot,previousOwner);
    }
    if(object->recordCount) {
    for(current=&object->scene;;current=current->owner) {
        if(current->flags.value&(1UL<<52)) return;
        if(current==changedRoot) break;
    }
    SCENE_OBJECT *oldBoundary=FindDetachedOwner(previousOwner);
    SCENE_OBJECT *newBoundary=FindDetachedOwner(object->scene.owner);
    if(!oldBoundary && !newBoundary) {
        func_0023BA40(object);
        func_0023B9C8(object);
    }
    }
}
