// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Relocate addresses in a selected span of the original global record table.
#include "m2c_prelude.h"
typedef struct Record { s32 unknown0[2]; u32 address; s32 unknown1[2]; } Record;
extern Record D_0046FF48[];
void func_00235D78(s32 first, s32 count, u32 size, u32 old_base, u32 new_base) {
    s32 end = first + count;
    u32 old_end = old_base + size;
    while (first < end) {
        Record *record = &D_0046FF48[first];
        u32 address = record->address;
        if (address >= old_base && address < old_end) {
            record->address = new_base + (address - old_base);
        }
        first++;
    }
}
