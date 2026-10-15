// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
typedef void (SCENE_OBJECT::*SceneActivationMember)(void *);
typedef char CheckActivationMember8[sizeof(SceneActivationMember)==8?1:-1];
extern "C" void func_0015DC68(void *,void *,SceneActivationMember,void *);
typedef unsigned int SceneActivationVector __attribute__((mode(TI)));
struct SceneActivationAnimation { char prefix[0xDC];void *pending; };
struct SceneActivationState {
    SCENE_OBJECT scene;
    char pad68[0xD8-0x68];
    SceneActivationAnimation *animation;
};
struct SceneActivationMode { char prefix[0x2C];int enabled; };
struct SceneActivationGame { char prefix[0x4DFC];SceneActivationMode *mode; };
struct SceneActivationMatrix { char prefix[0x30];SceneActivationVector position; };
extern "C" SceneActivationGame D_00475480;
extern "C" SceneActivationMember D_00326E88;
extern "C" void func_001C78A0(void *);
extern "C" void func_0028E768(void *);
extern "C" void func_0023B9C8(void *);
extern "C" void *func_001ED678(SceneActivationVector,int);
extern "C" void func_0023C750(void *,void *);
extern "C" void func_002BE8D0(void *,int);
struct SceneActivationScope { ~SceneActivationScope() { func_002BE8D0(this,2); } };
typedef SceneActivationMatrix *(*SceneActivationMatrixMethod)(void *);
typedef char CheckActivationScope1[sizeof(SceneActivationScope)==1?1:-1];
typedef char CheckActivationStateE0[sizeof(SceneActivationState)==0xE0?1:-1];

extern "C" void func_0023BAB8(SceneActivationState *object) {
    SceneActivationScope scope;
    func_001C78A0(object);
    func_0028E768(object);
    func_0023B9C8(object);
    int tagged=object->scene.field3C;
    if((tagged^1)&1) *(int *)tagged|=0x14;
    else object->scene.field3C=tagged|0x14;
    void *pending=object->animation?object->animation->pending:0;
    if(pending) {
        if(D_00475480.mode && D_00475480.mode->enabled) {
            SCENE_VIRTUAL_ENTRY *entry=&object->scene.vtable[36];
            SceneActivationMatrix *matrix=((SceneActivationMatrixMethod)entry->Simple)((char *)object+entry->delta);
            func_0023C750(object,func_001ED678(matrix->position,1));
        } else {
            func_0015DC68(&D_00475480,object,D_00326E88,0);
        }
    }
    for(SCENE_OBJECT *child=object->scene.children.first;child!=object->scene.anchor;child=child->previous)
        CallScene(child,11);
}
