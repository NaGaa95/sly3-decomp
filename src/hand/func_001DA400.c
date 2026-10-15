// Check the strict 50-unit tolerance against the owner coordinate.
#include "m2c_prelude.h"
s32 func_001DA400(void *state) {
 return fabsf(M2C_FIELD(M2C_FIELD(state, void **, 0x10), f32 *, 0x10F8) - M2C_FIELD(state, f32 *, 0x38)) < 50.0f;
}
