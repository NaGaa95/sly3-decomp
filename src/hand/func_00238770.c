#include "owned_record_list_api.h"
// Decrement the stored reference count and notify the referenced object through its original adjusted virtual method.
// Reference algorithm: src/hand/func_001FBAF8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct PMF {
    short adjustment;
    short reserved;
    void (*method)(void *);
};
struct O {
    char prefix[0xC];
    struct PMF *vtable;
};
struct R {
    struct O *object;
    int count;
};
void func_00238770(void *receiver) {
    struct R *record = (struct R *)receiver;
    struct O *object;
    struct PMF *slot;
    --record->count;
    object=record->object;
    slot=object->vtable+92;
    slot->method((char *)object+slot->adjustment);
}
