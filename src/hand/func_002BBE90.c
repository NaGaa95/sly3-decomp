// Construct the inherited object, clear the stored state fields, install its derived vtable, and return the receiver.
// Reference algorithm: src/hand/func_00146EE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00351D28[];
struct S { char unknown_0[0xC]; void * vtable; char unknown_10[0x4C]; int value_5C; };
struct S *func_002B8670(struct S *object);
struct S *func_002BBE90(struct S *object)
{
    func_002B8670(object);
    object->value_5C = 0;
    object->vtable = D_00351D28;
    return object;
}
