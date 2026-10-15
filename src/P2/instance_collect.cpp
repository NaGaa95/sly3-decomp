// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Collect a child's related pointers within a temporary slot-allocation mark.
#include "dmas.h"
#include "scene.h"
#include "heap_frame_api.h"

extern "C" void func_001FC338(unsigned int game,int owner,int count,void **objects);

inline ALLOCREQ *CollectRequest(ALLOCREQ *request,int bytes,int alignment)
{
    request->cb=bytes;
    request->cbAlign=alignment;
    return request;
}

extern "C" void func_001FC3A0(void *game,void *owner,SCENE_OBJECT *child)
{
    char frame[16];
    func_001D2770(frame);
    ALLOCREQ request;
    SCENE_OBJECT **base=(SCENE_OBJECT **)PvAllocSlot(CollectRequest(&request,0x600,16));
    SCENE_OBJECT **cursor=base;
    SCENE_VIRTUAL_ENTRY *collect=&child->vtable[28];
    ((void (*)(void *,void *,SCENE_OBJECT ***,SCENE_OBJECT **))collect->Simple)
        ((char *)child+collect->delta,owner,&cursor,base+0x180);
    func_001FC338((unsigned int)game,(int)owner,cursor-base,(void **)base);
    func_001D2798(frame,2);
}
