#include "m2c_prelude.h"
typedef struct Record { s32 first, second, third; } Record;
typedef struct RecordQueue { u8 unknown[0x44]; s32 count; Record *entries; } RecordQueue;
void func_0015E348(RecordQueue *state, s32 first, s32 second) {
 s32 count = state->count;
 if (count < 0x100) {
  Record *entry = &state->entries[count]; entry->first = first; entry->second = second;
  state->count = state->count + 1;
 }
}
