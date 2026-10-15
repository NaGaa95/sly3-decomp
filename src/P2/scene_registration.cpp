// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct SceneBinding { char prefix[0x60]; SCENE_OBJECT *root; };
struct SceneRegistrationState {
    SCENE_OBJECT scene;
    char pad68[0xDC-0x68]; SceneBinding *binding;
    char padE0[0x128-0xE0]; unsigned long registrationFlags;
};
struct SceneBindingList { void *first,*last; int memberOffset; };
extern "C" SceneBindingList D_00479938;
extern "C" void func_001C85C0(void *);
extern "C" void func_001C85E8(void *);
extern "C" void func_00211F18(void *);
extern "C" void func_00211F90(void *);
extern "C" void func_0011B028(void *,void *);
extern "C" int func_0011B0C0(void *,void *);
extern "C" void func_0011AF60(void *,void *);
extern "C" void func_002BE8D0(void *,int);
struct SceneRegistrationScope { ~SceneRegistrationScope() { func_002BE8D0(this,2); } };
typedef char CheckScope1[sizeof(SceneRegistrationScope)==1?1:-1];
typedef char CheckRegistrationPrefix130[sizeof(SceneRegistrationState)==0x130?1:-1];
typedef char CheckBindingPrefix64[sizeof(SceneBinding)==0x64?1:-1];
extern "C" void func_0023CE08(void *receiver) {
    SceneRegistrationState *object=(SceneRegistrationState *)receiver;
    SceneRegistrationScope scope;
    func_001C85C0(object);
    func_00211F18(object);
    for(SCENE_OBJECT *child=object->scene.children.first;child!=object->scene.anchor;child=child->previous)
        CallScene(child,24);
    if(object->binding && object->binding->root==&object->scene) {
        CallScene(&object->scene,54);
        func_0011B028(&D_00479938,object->binding);
    }
}
extern "C" void func_0023CEC0(void *receiver) {
    SceneRegistrationState *object=(SceneRegistrationState *)receiver;
    SceneRegistrationScope scope;
    func_001C85E8(object);
    if(object->registrationFlags&8L) {
        int value=object->scene.field3C;
        if((value^1)&1) value=*(int *)value;
        if(value&8) func_00211F90(object);
    }
    for(SCENE_OBJECT *child=object->scene.children.first;child!=object->scene.anchor;child=child->previous)
        CallScene(child,25);
    if(object->binding && object->binding->root==&object->scene) {
        if(!func_0011B0C0(&D_00479938,object->binding))func_0011AF60(&D_00479938,object->binding);
        CallScene(&object->scene,54);
    }
}
