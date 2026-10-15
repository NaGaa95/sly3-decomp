// Set one of the two indexed 32-bit fields when the index is in range.
#include "m2c_prelude.h"
typedef struct IndexedPair { u8 unknown[0x10]; s32 entries[2]; } IndexedPair;
void func_001856E0(IndexedPair *state, u32 index, s32 value) {
 if (index < 2) state->entries[index] = value;
}
