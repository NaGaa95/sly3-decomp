// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
#include "mat.h"
struct SceneInsertState;
struct SceneInsertTransform {
    char prefix[0x40];
    MATRIX4 matrix;
    char pad80[0xA4-0x80];
    int generation;
};
struct SceneInsertRecord {
    SceneInsertTransform *source;
    SCENE_OBJECT *owner;
    char pad8[0x18-8];
    unsigned long flags;
    char pad20[0x30-0x20];
    MATRIX4 matrix;
    char pad70[0xB8-0x70];
    int generation;
    int stamp;
    int mode;
    char padC4[0xD0-0xC4];
};
struct SceneInsertBinding {
    char prefix[0x34];
    SCENE_LIST members;
    char pad40[0x60-0x40];
    SceneInsertState *root;
};
struct SceneInsertState {
    SCENE_OBJECT scene;
    char pad68[0xDC-0x68];
    SceneInsertBinding *binding;
};
extern "C" void func_0023B6A0(void *);
extern "C" int func_0011B0C0(void *,void *);
extern "C" void func_0011AF60(void *,void *);
extern "C" void func_0023C840(SceneInsertRecord *);
extern "C" void func_0023E228(void *);
typedef int (*SceneInsertPredicate)(void *);
typedef char CheckRecordD0[sizeof(SceneInsertRecord)==0xD0?1:-1];
typedef char CheckStateE0[sizeof(SceneInsertState)==0xE0?1:-1];
extern "C" void func_0023B720(SceneInsertState *object,SceneInsertRecord *record) {
    func_0023B6A0(object);
    if(func_0011B0C0(&object->binding->members,record)) return;
    func_0011AF60(&object->binding->members,record);
    SceneInsertTransform *source=record->source;
    record->matrix=source->matrix;
    int generation=source->generation;
    record->stamp=-1;
    record->generation=generation;
    func_0023C840(record);
    record->mode=-1;
    SCENE_VIRTUAL_ENTRY *entry=&object->scene.vtable[66];
    if(!((SceneInsertPredicate)entry->Simple)((char *)object+entry->delta))
        func_0023E228(object);
}
