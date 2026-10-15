// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "actor_state_resource_api.h"

struct PendingTransitionState {
    char prefix[0x164];
    int enabled;
    float deadline;
};
struct PendingTriggerLink { PendingTriggerLink *next; };
struct PendingCleanupToken {};

extern "C" {
extern char D_00475480[];
extern float D_0036BB98;
extern PendingTriggerLink *D_00479BE0;
void func_001F7700(char *, int);
int func_001F7030(void *, void *);
void func_002BE8A8(void *, int);

void func_001F7240(PendingTransitionState *source)
{
    if (!source->enabled)
        return;
    if (source->deadline < D_0036BB98) {
        func_001F7700((char *)source, (int)func_001F4AD0(D_00475480, 0));
        return;
    }
    PendingCleanupToken cleanup;
    for (PendingTriggerLink *link = D_00479BE0; link; link = link->next) {
        if (func_001F7030(source, link))
            break;
    }
    func_002BE8A8(&cleanup, 2);
}
}
