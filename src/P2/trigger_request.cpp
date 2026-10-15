// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "actor_state_resource_api.h"

struct TriggerRuntime { char prefix[0x60]; char *type_object; };
struct TriggerFilterObject { char prefix[0xDC]; TriggerRuntime *runtime; };
struct TriggerFilterShape {
    void *transform;
    TriggerFilterObject *object;
    char reserved8[0x18-8];
    unsigned long flags;
};
struct TriggerActor;
struct TriggerActorHandle { TriggerActor *object; };
struct TriggerActor { char prefix[0x14]; TriggerActorHandle *handle; };
struct TriggerRequestInfo {
    char prefix[0x14];
    TriggerActor *object;
    char reserved18[0x50-0x18];
    unsigned int flags;
};
struct TriggerRequestSource { char prefix[0x164]; int enabled; };

extern "C" {
extern char D_00475480[];
int func_0013B500(char *object, int category);
void func_001F7700(char *receiver, int object);

int func_001F69F8(void *unused_context, TriggerFilterShape *shape)
{
    if (shape->flags & 0x10000UL)
        return 0;
    char *object = shape->object->runtime->type_object;
    if (func_0013B500(object, 0x31) || func_0013B500(object, 0x59))
        return 0;
    return 1;
}

int func_001F72D8(void *receiver, TriggerRequestInfo *info)
{
    TriggerRequestSource *source = (TriggerRequestSource *)receiver;
    if (source->enabled) {
        if (info->flags & 2) {
            char *actor;
            if (func_0013B500((char *)info->object, 0x31))
                actor = (char *)info->object;
            else if (func_0013B500((char *)info->object->handle->object, 0x31))
                actor = (char *)info->object->handle->object;
            else
                actor = (char *)func_001F4AD0(D_00475480, 0);
            func_001F7700((char *)receiver, (int)actor);
            return 1;
        }
    }
    return 0;
}
}
