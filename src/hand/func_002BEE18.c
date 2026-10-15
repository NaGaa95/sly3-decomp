// Construct the original base object, install the derived vtable at offset 0xE8, and return the receiver.
// Reference algorithm: src/hand/func_00182E80.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00361E88[];
struct S { char prefix[0xE8]; void *vtable; };
struct S *func_002BEC40(struct S *object);
struct S *func_002BEE18(struct S *object)
{
    func_002BEC40(object);
    object->vtable = D_00361E88;
    return object;
}
