// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Retry one child's related pointers before restoring the temporary heap mark.
#include "dmas.h"
#include "scene.h"
#include "heap_frame_api.h"
extern "C" void func_001FC520(unsigned int,int,int,SCENE_OBJECT **);
inline ALLOCREQ *CollectRequest(ALLOCREQ *request,int bytes,int alignment)
{
    request->cb=bytes;
    request->cbAlign=alignment;
    return request;
}
extern "C" void func_001FC5E0(unsigned int game,int owner,SCENE_OBJECT *child)
{
    char frame[16];
    func_001D2770(frame);
    ALLOCREQ request;
    SCENE_OBJECT **base=(SCENE_OBJECT **)PvAllocSlot(CollectRequest(&request,0x10000,16));
    SCENE_OBJECT **cursor=base;
    SCENE_VIRTUAL_ENTRY *collect=&child->vtable[28];
    ((void (*)(void *,int,SCENE_OBJECT ***,SCENE_OBJECT **))collect->Simple)
        ((char *)child+collect->delta,owner,&cursor,base+0x4000);
    func_001FC520(game,owner,cursor-base,base);
    func_001D2798(frame,2);
}
