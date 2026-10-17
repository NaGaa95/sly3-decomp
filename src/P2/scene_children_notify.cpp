// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "scene.h"
extern "C" void func_001FAD68(SCENE_OBJECT *object, int argument);
extern "C" void func_002BE8D0(void *scope, int flags);
struct ChildScope {
    ~ChildScope() { func_002BE8D0(this, 2); }
};
extern "C" void func_001FAF38(SCENE_OBJECT *object, int argument)
{
    func_001FAD68(object, argument);
    ChildScope scope;
    for (SCENE_OBJECT *child = object->children.first; child; child = child->previous) {
        SCENE_VIRTUAL_ENTRY *entry = &child->vtable[27];
        ((void (*)(void *, int, int))entry->Simple)((char *)child + entry->delta, argument, 0);
    }
}
