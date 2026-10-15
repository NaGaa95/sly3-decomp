// Original GCC member-pointer metadata proves the function boundary.
#include "m2c_prelude.h"
typedef struct Pair { s32 first, second; } Pair;
typedef struct Record { u8 unknown0[0x14]; f32 value; Pair pair; u8 unknown1[0x40]; } Record;
typedef struct State { u8 unknown[0x190]; Record entries[1]; } State;
void func_00207568(State *state, s32 index, f32 value, const Pair *pair) {
    Record *record = &state->entries[index];
    record->value = value;
    record->pair = *pair;
}
