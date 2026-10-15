// Update the inherited object and apply the stored128-bit reference value to its owner when present.
// Reference algorithm: src/hand/func_00132100.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int QWORD __attribute__((mode(TI)));
struct R { char prefix[0x30]; QWORD value; };
struct S { char prefix[0x48]; struct R *record; char unknown[0x1D0 - 0x4C]; void *owner; };
void func_0023D0E8(struct S *object);
void func_0012F4F8(void *owner, QWORD value);
void func_0020F798(struct S *object)
{
    func_0023D0E8(object);
    if (object->owner) func_0012F4F8(object->owner, object->record->value);
}
