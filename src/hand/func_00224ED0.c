// Integer and float argument banks follow the original EE ABI independently.
#include "m2c_prelude.h"
typedef struct Vector { f32 x, y, z; s32 tag; } Vector;
typedef struct Record {
    s32 first;
    u8 unknown0[0x14];
    Vector first_vector;
    u8 unknown1[0x88];
    s32 second;
    u8 unknown2[0x14];
    Vector second_vector;
    u8 unknown3[0x98];
} Record;
typedef struct State { u8 unknown[0x178]; s32 count; Record *entries; } State;
void func_00224ED0(State *state, s32 first, f32 x, f32 y, f32 z, s32 first_tag,
                   s32 second, f32 u, f32 v, f32 w, s32 second_tag) {
    s32 count = state->count;
    if (count < 64) {
        Record *record = &state->entries[count];
        Vector *vector;
        state->count = count + 1;
        record->first = first;
        vector = &record->first_vector;
        vector->x = x;
        vector->y = y;
        vector->z = z;
        vector->tag = first_tag;
        record->second = second;
        vector = &record->second_vector;
        vector->x = u;
        vector->y = v;
        vector->z = w;
        vector->tag = second_tag;
    }
}
