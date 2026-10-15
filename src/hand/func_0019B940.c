// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original callers retain the a0 context and pass count/records in a1/a2.
// Reset the identifier at the start of each sixteen-byte record.
#include "m2c_prelude.h"
typedef struct Record { s32 identifier; u32 reserved[3]; } Record;
void func_0019B940(u32 context, s32 count, Record *records) {
    if (count > 0) {
        do {
            count -= 1;
            records->identifier = -1;
            records += 1;
        } while (count != 0);
    }
}
