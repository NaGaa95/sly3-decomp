// Finish the base scene event, then select the matching local completion state.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene_mode.h"
extern "C" void func_001F4548(SCENE_MODE_OBJECT *,int);
extern "C" void func_001CAC30(SCENE_MODE_OBJECT *,int);
extern "C" void func_001CAAC0(SCENE_MODE_OBJECT *object,int event) {
    func_001F4548(object,event);
    if(event==-1) {
        if(object->state1B4>=6)goto reset;
        if(object->state1B4<4)goto reset;
        func_001CAC30(object,5);
        return;
reset:  func_001CAC30(object,0);
    }
}
