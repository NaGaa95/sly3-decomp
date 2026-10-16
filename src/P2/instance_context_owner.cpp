// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "instance_apply.h"
extern "C" int func_001FA5B8(int handle);
extern "C" int func_001FA5C0(int handle);

extern "C" void *func_001FC118(void *receiver)
{
    SCENE_OBJECT *object=(SCENE_OBJECT *)receiver;
    INSTANCE_APPLY_CONTEXT *context=(INSTANCE_APPLY_CONTEXT *)object->context;
    if(!context || !context->reserved24)
        return 0;
    int tableIndex=func_001FA5B8(context->handle);
    int instanceIndex=func_001FA5C0(((INSTANCE_APPLY_CONTEXT *)object->context)->handle);
    INSTANCE_SELECTION_TABLE *table=&D_00475480.tables[tableIndex];
    INSTANCE_SELECTION_ENTRY *entries=table->entries;
    if(!entries)
        return 0;
    return entries[instanceIndex-table->first].owner;
}
