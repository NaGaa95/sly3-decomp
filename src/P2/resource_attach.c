// SLY3_CFLAGS: -Os -G0
#include "animation_ensure_api.h"

struct AttachmentRetainMethod { short adjustment, reserved; void *function; };
struct AttachmentRetainedView {
    unsigned char prefix[0xC];
    struct AttachmentRetainMethod *table;
};
struct AttachmentApplyRecord {
    int kind;
    void *resource;
    struct AttachmentRetainedView *retained;
    int flags;
};

void func_002397E8(void *, void *, int, int, void **);
void func_002591B0(void *, void *, int, void **);
void func_002594E0(void *, void *, int, void *);

void func_00254D38(struct AttachmentApplyRecord *record, void *owner,
                   int flags, float value)
{
    switch (record->kind) {
    case -1:
        break;
    case 0:
        func_00136908((struct ASEG *)record->resource, (struct ALO *)owner,
                       value, 1.0f, flags, (struct ASEGA **)&record->retained);
        ((void (*)(void *))record->retained->table[1].function)
            ((char *)record->retained + record->retained->table[1].adjustment);
        break;
    case 1:
        func_002397E8(record->resource, owner, -1, flags,
                       (void **)&record->retained);
        ((void (*)(void *))record->retained->table[1].function)
            ((char *)record->retained + record->retained->table[1].adjustment);
        break;
    case 2:
        func_002591B0(record->resource, owner, flags,
                       (void **)&record->retained);
        ((void (*)(void *))record->retained->table[1].function)
            ((char *)record->retained + record->retained->table[1].adjustment);
        break;
    case 3:
        record->retained = (struct AttachmentRetainedView *)((char *)owner + 0xFC0);
        func_002594E0(record->resource, owner, flags, record->retained);
        ((void (*)(void *))record->retained->table[1].function)
            ((char *)record->retained + record->retained->table[1].adjustment);
        break;
    }
}
