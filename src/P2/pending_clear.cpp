// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct PendingEntry { unsigned char prefix[0x18]; unsigned long flags; };
extern "C" void func_0023B720(SCENE_OBJECT *object);
extern "C" void func_0023B920(SCENE_OBJECT *object,PendingEntry *entry)
{
    unsigned long flags=entry->flags;
    if(flags&0x80000) {
        entry->flags=flags&~0x80000UL;
        int inherited=object->flags.fields.inherited;
        if(inherited)
            func_0023B720(object);
    }
}
