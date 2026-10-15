// Increment the reference count; virtual-table callers identify this helper.
#include "m2c_prelude.h"
typedef struct RefState { u8 unknown[0x10]; s32 references; } RefState;
void func_00239BB0(RefState *state) { ++state->references; }
