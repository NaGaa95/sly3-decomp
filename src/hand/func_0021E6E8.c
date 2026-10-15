// Run the inherited reset and clear the stored value at offset 0x28.
// Reference algorithm: src/hand/func_001752C0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x28]; int value; };
void func_0021E6B8(struct S *object);
void func_0021E6E8(struct S *object)
{
    func_0021E6B8(object);
    object->value = 0;
}
