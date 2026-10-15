// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original callers pass the common manager at 0x00475480 as owner.
// Update a matching key pair or insert it while retaining the original spare-slot rule.
#include "m2c_prelude.h"
typedef struct Record { s32 first_key, second_key, first_value, second_value; } Record;
s32 func_0025D350(void *owner, Record *entries, s32 capacity, s32 *count,
                 s32 first, s32 first_key, s32 second_key, s32 value) {
    s32 i = 0;
    if (*count > 0) {
        Record *record = entries;
        do {
            if (record->first_key == first_key &&
                (record->second_key == -1 || record->second_key == second_key)) {
                if (first) record->first_value = value;
                else record->second_value = value;
                return 1;
            }
            ++i;
            ++record;
        } while (i < *count);
    }
    if (*count + 1 >= capacity) return 0;
    {
        // The EE record table uses 32-bit byte addresses.
        Record *added = (Record *)((*count)++ * sizeof(Record) + (u32)entries);
        added->first_key = first_key;
        added->second_key = second_key;
        if (first) {
            added->first_value = value;
            added->second_value = -1;
        } else {
            added->second_value = value;
            added->first_value = -1;
        }
    }
    return 1;
}
