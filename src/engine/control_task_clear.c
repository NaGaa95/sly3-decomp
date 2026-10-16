// SLY3_CFLAGS: -Os -G0
#include "resource_attachment_api.h"
struct ControlClearOwner {
    char prefix[0x48];
    void *channel;
    char unaccessed4C[0x120-0x4C];
    unsigned long flags;
};
struct ControlClearState {
    char prefix[0x10];
    struct ControlClearOwner *owner;
    char unaccessed14[0xE8-0x14];
    void *task;
};
extern char D_00475480[];
void func_0028F068(void *owner, void *channel, int mode);
void func_0013CD10(void *game, void *owner);

void func_001328B0(struct ControlClearState *state)
{
    if (state->task) {
        func_001309D8(&state->task);
        func_0028F068(state->owner, state->owner->channel, 2);
        state->owner->flags &= ~(1UL << 58);
        func_0013CD10(D_00475480, state->owner);
    }
}
