#include "m2c_prelude.h"
typedef struct Record { s32 first, second; } Record;
typedef struct State { u8 unknown[0x1A4]; u32 count; Record entries[32]; } State;
void func_00260298(State *state, s32 value) {
    if (state->count < 32) {
        state->entries[state->count++].first = value;
    }
}
