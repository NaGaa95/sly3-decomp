// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct LinkedChild { unsigned char prefix[0xF0]; SCENE_OBJECT *link; };
struct ChildList { unsigned char prefix[0x30]; int count; SCENE_OBJECT *children[1]; };
extern "C" void func_0024BDF8(ChildList *list)
{
    for(int i=0;i<list->count;i++) {
        SCENE_OBJECT *child=list->children[i];
        int inherited=child->flags.fields.inherited;
        if(inherited) {
            SCENE_OBJECT *link=((LinkedChild *)child)->link;
            if(link)
                CallScene(link,8);
        }
    }
}
