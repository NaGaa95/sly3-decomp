// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Collect and notify all objects while the temporary pointer buffer is alive.
#include "dmas.h"
#include "scene.h"
#include "heap_frame_api.h"
struct INSTANCE_COLLECTION_GAME {
    char reserved[0x10];
    SCENE_OBJECT *first;
};
struct INSTANCE_COLLECTION_CURSOR {
    char reserved[4];
    SCENE_OBJECT **cursor;
};
extern "C" {
    void func_002BE8D0(void *,int);
    void func_001FC338(unsigned int,int,int,void **);
}
inline ALLOCREQ *CollectRequest(ALLOCREQ *request,int bytes,int alignment)
{
    request->cb=bytes;
    request->cbAlign=alignment;
    return request;
}
extern "C" void func_001FC458(INSTANCE_COLLECTION_GAME *game)
{
    char frame[16];
    func_001D2770(frame);
    ALLOCREQ request;
    SCENE_OBJECT **base=(SCENE_OBJECT **)PvAllocSlot(CollectRequest(&request,0x10000,16));
    INSTANCE_COLLECTION_CURSOR work;
    work.cursor=base;
    for(SCENE_OBJECT *child=game->first;child;child=child->previous) {
        SCENE_VIRTUAL_ENTRY *collect=&child->vtable[28];
        ((void (*)(void *,void *,SCENE_OBJECT ***,SCENE_OBJECT **))collect->Simple)
            ((char *)child+collect->delta,0,&work.cursor,base+0x4000);
    }
    func_002BE8D0(&work,2);
    func_001FC338((unsigned int)game,0,work.cursor-base,(void **)base);
    func_001D2798(frame,2);
}
