// SLY3_CFLAGS: -Os -G0
#include "actor_state_resource_api.h"
struct RuntimeModeView {
    unsigned char beforeRuntime[0xDC];
    void *runtime;
    int pendingMode;
};
void func_00189078(void *runtime,void *source,void *context);
int func_0013B500(void *object,int classID);
void func_001BE918(void *receiver);
extern unsigned char D_00475480[];
void func_0024D640(void *receiver,int mode)
{
    struct RuntimeModeView *object=receiver;
    if (object->runtime) {
        void *actor;
        func_00189078(object->runtime,(void *)2,receiver);
        actor=func_001F4AD0(D_00475480,0);
        if (actor && func_0013B500(actor,0x33))
            func_001BE918((char *)actor+0xF7C);
    } else object->pendingMode=mode;
}
