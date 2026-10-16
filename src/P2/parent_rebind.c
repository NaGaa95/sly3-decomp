// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "owner_parent_link.h"

struct ParentSlot { char storage[0x11C0]; };
struct ParentBinding { char prefix[8]; void **destination; };
struct ParentObject { char prefix[0xD4]; struct ParentBinding *binding; };
struct ParentGame {
    char prefix[0x4F6C];
    int count;
    struct ParentObject *objects[0];
};

extern struct ParentSlot D_0036E740[];
void *func_001F4B30(void *receiver);

void func_001F49C8(void *receiver, int slot_index)
{
    struct ParentGame *game = receiver;
    int i;
    for (i = 0; i < game->count; ++i) {
        struct ParentObject *object = game->objects[i];
        struct ParentBinding *binding = object->binding;
        struct ParentSlot *slot = &D_0036E740[slot_index];
        *binding->destination = func_001F4B30(slot);
        func_001C7A00(object, func_001F4B30(slot), 0);
    }
}
