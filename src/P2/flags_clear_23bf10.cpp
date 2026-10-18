// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
extern "C" void func_002BE8D0(void *,int);
struct ChildScope { ~ChildScope() { func_002BE8D0(this,2); } };
extern "C" void func_0023BF10(SCENE_OBJECT *object,int bits)
{
    ChildScope scope;
    int clear=bits;
    if(bits&4) {
        int tagged=object->field3C;
        unsigned int current=((tagged^1)&1)?*(unsigned int *)tagged:tagged;
        if(current&0x20)
            clear=bits&~4;
    }
    int tagged=object->field3C;
    if((tagged^1)&1) *(int *)tagged&=~clear;
    else object->field3C=tagged&~clear;
    for(SCENE_OBJECT *child=object->children.first;child!=object->anchor;child=child->previous) {
        SCENE_VIRTUAL_ENTRY *entry=&child->vtable[52];
        ((void (*)(void *,int))entry->Simple)((char *)child+entry->delta,bits);
    }
}
