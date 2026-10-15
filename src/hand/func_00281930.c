// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Append the identifier and a 128-bit payload to the 32-byte record array.
#include "m2c_prelude.h"
typedef struct Record { s32 identifier; u8 unknown[0xC]; s128 payload; } Record;
typedef struct QueueState { u8 unknown[0x174]; s32 count; Record *entries; } QueueState;
void func_00281930(QueueState *state, s32 identifier, s128 payload) {
 s32 count = state->count;
 if (count < 256) {
  state->entries[count].identifier = identifier;
  state->entries[state->count].payload = payload;
  state->count = state->count + 1;
 }
}
