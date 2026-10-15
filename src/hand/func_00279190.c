// Append related values to the parallel inline arrays.
#include "m2c_prelude.h"
typedef struct State { u8 unknown[0x158]; u32 count; s32 first[32]; s32 second[32]; } State;
void func_00279190(State *state, s32 first, s32 second) {
 u32 index = state->count;
 if (index < 32) {
  state->first[index] = first;
  index = state->count;
  state->second[index] = second;
  state->count = index + 1;
 }
}
