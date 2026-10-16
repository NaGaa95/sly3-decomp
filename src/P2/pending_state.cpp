// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct PendingView { unsigned char prefix[0x294]; int pending; };
extern char D_00468D30[];
extern "C" int func_0025E188(void);
extern "C" int func_0025E250(int state,void *record);
extern "C" int func_002796A0(SCENE_OBJECT *object)
{
    int inherited=object->flags.fields.inherited;
    if(!inherited)
        return 0;
    if(((PendingView *)object)->pending) {
        if(func_0025E250(func_0025E188(),D_00468D30))
            return 0;
    }
    return 1;
}
