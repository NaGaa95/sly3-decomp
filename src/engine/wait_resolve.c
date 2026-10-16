// SLY3_CFLAGS: -Os -G0
#include "resource_selected_child_pointer_api.h"
struct WaitResolveState {
    char unaccessed[0x34];
    void *context;
};
struct WaitResolveGame { unsigned char unused; };
extern struct WaitResolveGame D_00475480;
void *func_0017E1B8(void *game,int flags,int key,void *context);
int func_0013B500(void *object,int kind);
void *func_00197B98(struct WaitResolveState *state,int key)
{
    void *context=state->context;
    int kind=context?4:5;
    void *object=func_0017E1B8(&D_00475480,kind,key,context);
    if(object&&func_0013B500(object,8))
        object=func_001FBEC0(object);
    return object;
}
