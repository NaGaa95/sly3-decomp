// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct SceneRebindState;
struct SceneRebindBinding { char prefix[0x60]; SceneRebindState *root; };
struct SceneRebindState {
    SCENE_OBJECT scene;
    char pad68[0xDC-0x68];
    SceneRebindBinding *binding;
};
extern "C" char D_00475480[];
extern "C" SceneRebindState *func_0023B650(SceneRebindState *);
extern "C" int func_0017E208(void *,int,int,void *,int,SceneRebindState **);
extern "C" void func_0023BA40(void *);
extern "C" void func_0023B9C8(void *);
extern "C" void func_0013CD10(void *,void *);
extern "C" void func_0023E228(void *);
typedef char CheckRebindE0[sizeof(SceneRebindState)==0xE0?1:-1];
extern "C" void func_0023EA88(SceneRebindState *object) {
    SceneRebindState *items[64];
    int inherited=object->scene.flags.fields.inherited;
    if(!inherited || !object->binding) return;
    if(func_0023B650(object)!=object->binding->root) {
        int count=func_0017E208(D_00475480,1,0x2F,object,64,items);
        for(int index=0;index<count;++index) {
            SceneRebindState *child=items[index];
            if(child->binding) {
                SceneRebindState *root=func_0023B650(child);
                if(root!=child->binding->root) {
                    func_0023BA40(child);
                    if(!root->binding) {
                        SCENE_VIRTUAL_ENTRY *entry=&root->scene.vtable[57];
                        root->binding=(SceneRebindBinding *)entry->Query((char *)root+entry->delta);
                        func_0013CD10(D_00475480,root);
                    }
                    child->binding=root->binding;
                    func_0023B9C8(child);
                }
            }
        }
    }
    func_0013CD10(D_00475480,object);
    func_0023E228(object);
}
