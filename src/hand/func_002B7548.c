// Construct the inherited object, clear the stored state fields, install its derived vtable, and return the receiver.
// Reference algorithm: src/hand/func_00146EE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00359C58[];
struct S { char unknown_0[0xC]; void * vtable; char unknown_10[0x2F0]; int value_300; };
struct S *func_002B7510(struct S *object);
struct S *func_002B7548(struct S *object)
{
    func_002B7510(object);
    object->value_300 = 0;
    object->vtable = D_00359C58;
    return object;
}
