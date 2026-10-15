// Compare the remaining interval against the strict five-unit threshold.
#include "m2c_prelude.h"
extern f32 D_0036BB98;
s32 func_002564C8(void *state) { return D_0036BB98 - M2C_FIELD(state, f32 *, 4) > 5.0f; }
