// Clear the stored referenced word when its pointer is present.
// Reference algorithm: src/hand/func_00221120.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { char prefix[0x14]; int *value; };
struct S { char prefix[0x288]; struct R *record; };
void func_0024DCE0(struct S *object)
{
    if(object->record->value)*object->record->value=0;
}
