// Run the inherited reset and clear the stored value at offset 0x550.
// Reference algorithm: src/hand/func_001752C0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x550]; int value; };
void func_0023C970(struct S *object);
void func_00214928(struct S *object)
{
    func_0023C970(object);
    object->value = 0;
}
