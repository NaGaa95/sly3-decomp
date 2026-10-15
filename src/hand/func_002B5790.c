// Return the original stored64-bit resource flag at bit21.
// Reference algorithm: src/hand/func_00221120.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef signed int I64 __attribute__((mode(DI)));
struct R { char prefix[0x18]; I64 flags; };
struct S { char prefix[0x24]; struct R *record; };
int func_002B5790(struct S *object)
{
    return (int)((object->record->flags << 11) >> 32) & 1;
}
