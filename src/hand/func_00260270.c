#include "m2c_prelude.h"
typedef struct Record { s32 first, second; } Record;
typedef struct State { u8 unknown[0x120]; u32 count; Record entries[16]; } State;
void func_00260270(State *state, s32 value) {
    if (state->count < 16) {
        state->entries[state->count++].first = value;
    }
}
