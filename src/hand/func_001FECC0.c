// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// State transitions notify through a GCC adjustment/function vtable entry.
// The original call sites explicitly initialize all six EE argument registers.
#include "m2c_prelude.h"

typedef s32 (*NotifyCallback)(void *, s32, s32, s32, s32, s32);

extern f32 D_0036BB98;

void func_001FECC0(void *state, s32 value) {
    s32 previous = M2C_FIELD(state, s32 *, 0xD0);
    if (previous != value) {
        if (previous == 0) {
            void *table = M2C_FIELD(state, void **, 0xC);
            M2C_FIELD(table, NotifyCallback *, 0x1C)(
                (u8 *)state + M2C_FIELD(table, s16 *, 0x18), 6, 0, 0, 0, 0);
        }
        M2C_FIELD(state, s32 *, 0xD0) = value;
        M2C_FIELD(state, f32 *, 0xD4) = D_0036BB98;
        if (value == 0) {
            void *table = M2C_FIELD(state, void **, 0xC);
            M2C_FIELD(table, NotifyCallback *, 0x1C)(
                (u8 *)state + M2C_FIELD(table, s16 *, 0x18), 5, 0, 0, 0, 0);
        }
    }
}
