// Locate the first kind11 record with the requested integer key.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "animation_record_lookup_api.h"
struct LookupRecord20 *func_00136880(struct LookupLibrary *library, int key) {
    int index;
    for (index = 0; index < library->count90; ++index) {
        struct LookupRecord20 *record = &library->records94[index];
        if (record->kind4 == 11 && record->key8 == key)
            return record;
    }
    return 0;
}
