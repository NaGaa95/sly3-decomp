// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "scene.h"
#include "vector_intrinsics.h"
struct ActorMatrix { qword row[4]; };
struct Record { char prefix[0x160]; int flags; int identifier; int active; };
struct Holder { SCENE_OBJECT *owner; int state; float stamp; Record *record; };
extern "C" float D_0036BB98;
extern "C" void func_00240CB0(void *receiver,int option,void *owner,int flags,int identifier,int active,qword first,qword second,void *output);
extern "C" void func_00259F88(Holder *holder,int state)
{
    if(state!=holder->state) {
        int *slot=&holder->state;
        *slot=state;
        holder->stamp=D_0036BB98;
        if(state==2) {
            SCENE_VIRTUAL_ENTRY *entry=&holder->owner->vtable[36];
            qword position=((ActorMatrix *(*)(void *))entry->Simple)((char *)holder->owner+entry->delta)->row[3];
            entry=&holder->owner->vtable[38];
            qword second=((qword (*)(void *))entry->Simple)((char *)holder->owner+entry->delta);
            func_00240CB0(holder->record,0,holder->owner,holder->record->flags,holder->record->identifier,holder->record->active,position,second,0);
        }
    }
}
