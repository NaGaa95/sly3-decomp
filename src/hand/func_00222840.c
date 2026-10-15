// Run the inherited reset and clear the stored value at offset 0x30.
// Reference algorithm: src/hand/func_001752C0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x30]; int value; };
void func_00222868(struct S *object);
void func_00222840(struct S *object)
{
    func_00222868(object);
    object->value = 0;
}
