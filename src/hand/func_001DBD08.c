// Append a four-byte-aligned 64-byte record to the four-slot inline queue.
#include "m2c_prelude.h"
typedef struct Record { s32 fields[16]; } Record;
typedef struct State { u32 count; Record entries[4]; } State;
void func_001DBD08(State *state, const Record *record) {
    if (record && state->count < 4) {
        *(state->count++ + state->entries) = *record;
    }
}
