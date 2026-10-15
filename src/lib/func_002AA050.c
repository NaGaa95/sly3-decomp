// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
#include "runtime_mpeg_general_callback_access.h"

void *func_002AA050(RuntimeMpegGeneralCallbackOwner *owner, int index,
                   void *callback, void *context)
{
    RuntimeMpegGeneralCallbackState *state = owner->state;
    void *old = state->callbacks[index].callback;
    int saved_gp;
    state->callbacks[index].callback = callback;
    state->callbacks[index].context = context;
    __asm__ volatile("move %0, $gp" : "=r"(saved_gp));
    state->callbacks[index].saved_gp = saved_gp;
    return old;
}
