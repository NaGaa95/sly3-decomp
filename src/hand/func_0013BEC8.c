// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Test the original half-open class-ID range in the shared factory descriptor array.
#include "m2c_prelude.h"

#include "factory_descriptor.h"
typedef struct FactoryDescriptor Record;
s32 func_0013BEC8(s32 value, s32 category) {
    s32 result = 0;
    if (value >= category) {
        Record *record = (Record *)(category * sizeof(Record) + (u32)D_003409E0);
        result = value < record->type_end;
    }
    return result;
}
