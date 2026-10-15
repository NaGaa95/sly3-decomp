// Construct the original base object, install the derived vtable at offset 0x0, and return the receiver.
// Reference algorithm: src/hand/func_00182E80.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0035D968[];
struct S { void *vtable; };
struct S *func_002BE7E0(struct S *object);
struct S *func_002BE7F8(struct S *object)
{
    func_002BE7E0(object);
    object->vtable = D_0035D968;
    return object;
}
