// Four-byte-aligned two-word records produce the original unaligned doubleword copies.
#include "m2c_prelude.h"
typedef struct Pair { s32 first, second; } Pair;
typedef struct Slot { s32 first_active, second_active; Pair first, second, third, fourth; } Slot;
typedef struct State { u8 unknown[0x2B0]; Slot slots[6]; } State;
void func_0019DD38(State *state, u32 index, const Pair *first, const Pair *second) {
    if (index < 6) {
        Slot *slot = &state->slots[index];
        slot->first_active = 1;
        slot->first = *first;
        slot->second = *second;
    }
}
