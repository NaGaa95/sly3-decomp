// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
typedef void (SCENE_OBJECT::*SceneDeactivationMember)(void *);
typedef char CheckDeactivationMember8[sizeof(SceneDeactivationMember)==8?1:-1];
struct SceneDeactivationAnimation { char prefix[0xDC];void *pending; };
struct SceneDeactivationState {
    SCENE_OBJECT scene;
    char pad68[0xD8-0x68];
    SceneDeactivationAnimation *animation;
    char padDC[0x104-0xDC];float scale;float rate;
};
extern "C" unsigned char D_00475480[];
extern "C" SceneDeactivationMember D_00326E88;
extern "C" void func_001C7938(void *);
extern "C" void func_0023BA40(void *);
extern "C" void func_00240DB0(void *);
extern "C" void func_0015DD68(void *,int,void *,SceneDeactivationMember,void *);
extern "C" void func_0023C750(void *,void *);
struct SceneDeactivationIterator;
extern "C" SceneDeactivationIterator *D_0036AE94;
struct SceneDeactivationIterator {
    SCENE_LIST *list;
    SCENE_OBJECT **cursor;
    int offset;
    SceneDeactivationIterator *previous;
    SceneDeactivationIterator(SCENE_LIST *items):list(items),cursor((SCENE_OBJECT **)items),offset(items->memberOffset),previous(D_0036AE94) {
        D_0036AE94=this;
    }
    ~SceneDeactivationIterator() { D_0036AE94=previous; }
    SCENE_OBJECT *Next() {
        SCENE_OBJECT *item=*cursor;
        cursor=(SCENE_OBJECT **)((unsigned int)item+offset);
        return item;
    }
};
typedef char CheckDeactivationIterator16[sizeof(SceneDeactivationIterator)==16?1:-1];

extern "C" void func_0023BBE0(SceneDeactivationState *object) {
    func_001C7938(object);
    func_0023BA40(object);
    object->rate=0.0f;
    object->scale=1.0f;
    func_00240DB0(object);
    void *pending=object->animation?object->animation->pending:0;
    if(pending) {
        func_0015DD68(D_00475480,3,object,D_00326E88,0);
        func_0023C750(object,0);
    }
    SceneDeactivationIterator iterator(&object->scene.children);
    SCENE_OBJECT *child;
    while((child=iterator.Next()) && !(child->flags.value&(1UL<<52)))
        CallScene(child,12);
}
