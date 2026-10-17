// SLY3_CFLAGS: -Os -G0
#include "deferred_callback_api.h"
struct ExitEntry { short delta, unused; void (*invoke)(void *); };
struct ExitObject { char prefix[0xC]; struct ExitEntry *vtable; char pad10[0xA0-0x10]; void *owner; };
extern unsigned char D_00475480[];
extern struct DEFERRED_PMF D_0031F920;
void func_001C7DC8(void *);
void func_00136820(struct ExitObject *object)
{
    func_001C7DC8(object);
    object->vtable[9].invoke((char *)object+object->vtable[9].delta);
    if(object->owner) func_0015DC68(D_00475480,object,D_0031F920,object->owner);
}
