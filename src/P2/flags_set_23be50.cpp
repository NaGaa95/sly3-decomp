// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-gcse -fno-cse-skip-blocks
#include "scene.h"
extern "C" void func_002BE8D0(void *,int);
struct ChildScope { ~ChildScope() { func_002BE8D0(this,2); } };
extern "C" void func_0023BE50(SCENE_OBJECT *object,unsigned int bits)
{
    int tagged=object->field3C;
    unsigned int current=((tagged^1)&1)?*(unsigned int *)tagged:tagged;
    if((current&0x24)==0x24)
        return;
    ChildScope scope;
    if((tagged^1)&1) *(unsigned int *)tagged|=bits;
    else object->field3C=tagged|bits;
    for(SCENE_OBJECT *child=object->children.first;child!=object->anchor;child=child->previous) {
        SCENE_VIRTUAL_ENTRY *entry=&child->vtable[51];
        ((void (*)(void *,unsigned int))entry->Simple)((char *)child+entry->delta,bits);
    }
}
