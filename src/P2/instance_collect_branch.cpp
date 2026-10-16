// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "scene.h"
extern "C" int func_001FC1F0(char *receiver,void *context);
extern "C" void func_002BE8D0(void *scope,int flags);

struct InstanceCollectionScope {
    ~InstanceCollectionScope() { func_002BE8D0(this,2); }
};

extern "C" void func_001FC290(SCENE_OBJECT *object,void *context,
                              SCENE_OBJECT ***cursor,SCENE_OBJECT **end)
{
    if(!func_001FC1F0((char *)object,context))
        return;
    InstanceCollectionScope scope;
    *(*cursor)++=object;
    for(SCENE_OBJECT *child=object->children.first;child;child=child->previous) {
        SCENE_VIRTUAL_ENTRY *entry=&child->vtable[28];
        ((void (*)(void *,void *,SCENE_OBJECT ***,SCENE_OBJECT **))entry->Simple)
            ((char *)child+entry->delta,context,cursor,end);
    }
}
