// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "scene.h"
extern "C" void func_001C9198(SCENE_OBJECT *object, int state);
extern "C" void func_001FC8F8(void *receiver, void *owner)
{
    SCENE_OBJECT *object = (SCENE_OBJECT *)receiver;
    SCENE_OBJECT *parent = (SCENE_OBJECT *)owner;
    object->flags.value |= 1UL << 59;
    if (parent && !(object->flags.value & (1UL << 54)))
        func_001C9198(object, ((unsigned char *)&parent->flags)[4]);
    SCENE_VIRTUAL_ENTRY *entry = &object->vtable[4];
    entry->Message((char *)object + entry->delta, 2, object);
}
