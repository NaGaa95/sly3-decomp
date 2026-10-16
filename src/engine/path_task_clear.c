// SLY3_CFLAGS: -Os -G0
#include "path_task_api.h"
#include "path_task_clear_api.h"

typedef struct ClearTaskRecord {
    void *object;
    unsigned char unaccessed4[44];
} ClearTaskRecord;

typedef struct ClearTaskOwner {
    unsigned char unaccessed0[0x4C];
    int count;
    ClearTaskRecord *records;
} ClearTaskOwner;

void func_0019A030(void *opaqueOwner)
{
    ClearTaskOwner *owner = opaqueOwner;
    int i;

    if (!owner->records)
        return;
    for (i = 0; i < owner->count; ++i) {
        ClearTaskRecord *record = &owner->records[i];
        if (record->object)
            func_00199118(owner, record, 0, 0);
    }
}
