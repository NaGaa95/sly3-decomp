// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct Machine {
    unsigned char prefix[0x463C];
    SCENE_OBJECT *single;
    SCENE_OBJECT *first;
    SCENE_OBJECT *second;
    unsigned char gap4648[0x4FA4 - 0x4648];
    int mode;
};
extern "C" {
void func_00166548(void *object);
SCENE_OBJECT *func_001F4AD0(Machine *machine, int index);
}
extern "C" void func_0025E8C0(Machine *machine, int mode)
{
    int i;
    if (mode == machine->mode)
        return;
    if (machine->mode) {
        CallScene(machine->first, 57);
        CallScene(machine->second, 57);
    } else {
        CallScene(machine->single, 57);
    }
    machine->mode = mode;
    if (mode) {
        CallScene(machine->first, 56);
        func_00166548(machine->first);
        CallScene(machine->second, 56);
        func_00166548(machine->second);
    } else {
        CallScene(machine->single, 56);
        func_00166548(machine->single);
    }
    for (i = 0; i < 2; i++) {
        SCENE_OBJECT *object = func_001F4AD0(machine, i);
        if (object) {
            SCENE_VIRTUAL_ENTRY *entry = &object->vtable[89];
            ((void (*)(void *, int))entry->Simple)((char *)object + entry->delta, machine->mode);
        }
    }
}
