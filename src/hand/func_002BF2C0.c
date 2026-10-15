// Return the nested owner resource value, or zero if either stored pointer is absent.
// Reference algorithm: src/hand/func_001477B0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { char prefix[0x10]; int value; };
struct T { char prefix[0xDC]; struct R *record; };
struct S { char prefix[0xD8]; struct T *owner; };
int func_002BF2C0(struct S *object)
{
    struct R *record = 0;
    if (object->owner) record = object->owner->record;
    return record ? record->value : 0;
}
