// Construct the original base object, install the derived vtable at offset 0x0, and return the receiver.
// Reference algorithm: src/hand/func_00182E80.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_003532D0[];
struct S { void *vtable; };
struct S *func_002BBCC0(struct S *object);
struct S *func_002BBC88(struct S *object)
{
    func_002BBCC0(object);
    object->vtable = D_003532D0;
    return object;
}
