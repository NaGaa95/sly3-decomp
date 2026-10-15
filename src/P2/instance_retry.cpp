// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Retry unresolved objects, compacting the borrowed array for at most sixteen passes.
#include "scene.h"
extern "C" void func_001FC520(unsigned int game,int owner,int count,SCENE_OBJECT **objects)
{
    SCENE_OBJECT **end=objects+count;
    int pass=0;
    do {
        SCENE_OBJECT **output=objects;
        for(SCENE_OBJECT **current=objects;current<end;current++) {
            SCENE_OBJECT *child=*current;
            SCENE_VIRTUAL_ENTRY *attempt=&child->vtable[30];
            if(!((int (*)(void *,int))attempt->Simple)((char *)child+attempt->delta,owner))
                *output++=child;
        }
        ++pass;
        if(output==objects)
            break;
        end=output;
    } while(pass<16);
}
