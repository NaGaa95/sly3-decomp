// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct SceneRemoveState;
struct SceneRemoveRecord {
    char prefix[0x18];
    unsigned long flags;
    char tail20[0xD0-0x20];
};
struct SceneRemoveBinding {
    char prefix[0x34];
    SCENE_LIST members;
    char pad40[0x60-0x40];
    SceneRemoveState *root;
};
struct SceneRemoveState {
    SCENE_OBJECT scene;
    char pad68[0xD0-0x68];
    int recordCount;
    SceneRemoveRecord *records;
    void *animation;
    SceneRemoveBinding *binding;
};
extern "C" char D_00475480[];
extern "C" int func_0011B0C0(void *,void *);
extern "C" void func_0011B028(void *,void *);
extern "C" int func_0011B0F0(void *);
extern "C" void func_001C1128(void *,SCENE_OBJECT *,SceneRemoveRecord *);
extern "C" void func_0025DE40(void *,SceneRemoveRecord *);
extern "C" void func_0023DF78(void *);
extern "C" void func_0013C138(void *,SceneRemoveBinding *);
extern "C" void func_0023E228(void *);
typedef int (*SceneRemovePredicate)(void *);
typedef char CheckRecordD0[sizeof(SceneRemoveRecord)==0xD0?1:-1];
typedef char CheckStateE0[sizeof(SceneRemoveState)==0xE0?1:-1];
extern "C" void func_0023B7E8(SceneRemoveState *object,SceneRemoveRecord *record) {
    int index;
    if(!object->binding) return;
    if(!func_0011B0C0(&object->binding->members,record)) return;
    func_0011B028(&object->binding->members,record);
    if(record->flags&(1UL<<20)) func_001C1128(D_00475480,0,record);
    func_0025DE40(D_00475480,record);
    func_0023DF78(object);
    if(func_0011B0F0(&object->binding->members)) {
        SceneRemoveBinding *binding=object->binding;
        binding->root->binding=0;
        object->binding=0;
        func_0013C138(D_00475480,binding);
    } else if(object->binding->root!=object) {
        index=object->recordCount;
        while(--index>=0) {
            if(func_0011B0C0(&object->binding->members,(SceneRemoveRecord *)(index*sizeof(SceneRemoveRecord)+(unsigned int)object->records))) break;
        }
        if(index<0) object->binding=0;
    }
    SCENE_VIRTUAL_ENTRY *entry=&object->scene.vtable[66];
    if(!((SceneRemovePredicate)entry->Simple)((char *)object+entry->delta))
        func_0023E228(object);
}
