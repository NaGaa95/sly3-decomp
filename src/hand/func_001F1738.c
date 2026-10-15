#include "m2c_prelude.h"
typedef struct Record { s32 type, reset, identifier, value; } Record;
typedef struct State { u8 unknown0[0x414]; Record entries[8]; s32 count; u8 unknown1[8]; s32 enabled; } State;
void func_001F1738(State *state, s32 value) {
    if (state->enabled) {
        Record *record = &state->entries[state->count++];
        record->type = 0x30A;
        record->reset = 0;
        record->identifier = -1;
        record->value = value;
    }
}
