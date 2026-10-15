// SLY3_CFLAGS: -Os -G0
#include "animation_ensure_api.h"
struct CleanupAnimationPrefix {
    char reserved0[0x40];
    float scaled_rate;
};
struct StateCleanupPrefix {
    char reserved0[0x30];
    struct CleanupAnimationPrefix *active;
};
void func_00137B00(void *runtime);
void func_0023A640(void *state);
void func_00239F58(struct StateCleanupPrefix *state)
{
    struct CleanupAnimationPrefix *active = state->active;
    if (active) {
        state->active = 0;
        if (active->scaled_rate < 0.0f)
            func_00137D08((struct SeekRuntime *)active, 0, 0.0f, active->scaled_rate, 1);
        else
            func_00137D08((struct SeekRuntime *)active, 2, 0.0f, active->scaled_rate, 1);
        func_00137B00(active);
        func_0023A640(state);
    }
}
