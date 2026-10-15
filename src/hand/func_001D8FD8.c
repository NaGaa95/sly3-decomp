#include "m2c_prelude.h"
s32 func_001D8FD8(void *state) {
 s32 result = 0;
 if (M2C_FIELD(state, s32 *, 0x3C) == 0) result = M2C_FIELD(state, f32 *, 0xD0) < 0.0f;
 return result;
}
