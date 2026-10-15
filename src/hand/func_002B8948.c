// Construct the original base object, install the derived vtable at offset 0x2C, and return the receiver.
// Reference algorithm: src/hand/func_00182E80.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0035BB68[];
struct S { char prefix[0x2C]; void *vtable; };
struct S *func_002B89A0(struct S *object);
struct S *func_002B8948(struct S *object)
{
    func_002B89A0(object);
    object->vtable = D_0035BB68;
    return object;
}
