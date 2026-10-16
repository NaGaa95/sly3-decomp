// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "instance_selection.h"
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024AEF8(CRef *output,int count,int type,void *values);
}

extern "C" CRef *func_001FBF40(CRef *output,INSTANCE_SELECTION_OWNER *owner)
{
    SCENE_OBJECT *objects[32];
    unsigned int count=0;
    INSTANCE_SELECTION_ENTRY *entry;
    for(entry=owner->head;entry && count<32;entry=entry->next) {
        int index=func_001FB5D8(owner,entry);
        objects[count++]=owner->table->objects[index];
    }
    func_0024AEF8(output,count,0x2002,objects);
    return output;
}
