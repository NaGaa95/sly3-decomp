// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Return the indexed record identifier, or -1 when the index is out of bounds.
#include "m2c_prelude.h"
typedef struct Entry { s32 identifier; s32 value; } Entry;
typedef struct State { u8 unknown[0x40]; s32 count; Entry *entries; } State;
s32 func_00239B80(State *state, s32 index) {
 if (index < 0 || index >= state->count) return -1;
 return state->entries[index].identifier;
}
