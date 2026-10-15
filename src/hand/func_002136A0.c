#include "m2c_prelude.h"
typedef struct Record { s32 first, second, third; } Record;
typedef struct RecordQueue { u8 unknown[0x19C]; u32 count; Record entries[12]; } RecordQueue;
void func_002136A0(RecordQueue *state, s32 first, s32 second, s32 third) {
 u32 count = state->count;
 if (count < 12) { Record *entry; state->count = count + 1; entry = &state->entries[count]; entry->first = first; entry->second = second; entry->third = third; }
}
