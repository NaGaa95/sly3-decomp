// Set state three through the original transition method and clear the receiver flags.
// Reference algorithm: src/hand/func_00120CC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x20]; int flags; };
void func_00210C90(struct S *object, int state);
void func_00210A60(struct S *object)
{
    func_00210C90(object, 3);
    object->flags = 0;
}
