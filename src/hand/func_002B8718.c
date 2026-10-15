// Construct the original base object, install the derived vtable at offset 0x14, and return the receiver.
// Reference algorithm: src/hand/func_00182E80.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00350DE8[];
struct S { char prefix[0x14]; void *vtable; };
struct S *func_002B8700(struct S *object);
struct S *func_002B8718(struct S *object)
{
    func_002B8700(object);
    object->vtable = D_00350DE8;
    return object;
}
