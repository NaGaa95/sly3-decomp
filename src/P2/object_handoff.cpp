// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct SelectedObjectHandoffView {
    unsigned char prefix[0x74]; SCENE_OBJECT *object; int active;
};
extern "C" void func_00273ED0(void *,void *,void *,int);
extern "C" void func_00273E48(void *,void *,void *,int);
extern "C" void func_0022B090(void *receiver,SCENE_OBJECT *object)
{
    SelectedObjectHandoffView *state=(SelectedObjectHandoffView *)receiver;
    if(state->object) {
        func_00273ED0(state->object,0,0,1);
        if(state->active)
            CallScene(state->object,9);
        state->object=0;
    }
    if(!object)
        return;
    state->object=object;
    int inherited=object->flags.fields.inherited;
    state->active=!inherited;
    if(state->active)
        CallScene(object,8);
    func_00273E48(state->object,0,0,1);
}
