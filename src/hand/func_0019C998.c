#include "m2c_prelude.h"
typedef struct Record { s32 first, second; u8 unknown[0x10]; } Record;
typedef struct RecordQueue { u8 unknown[0x28C]; u32 count; Record entries[4]; } RecordQueue;
void func_0019C998(RecordQueue *state, s32 first, s32 second) {
 u32 count = state->count;
 if (count < 4) { Record *entry; state->count = count + 1; entry = &state->entries[count]; entry->first = first; entry->second = second; }
}
