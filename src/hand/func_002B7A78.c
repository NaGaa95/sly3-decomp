// Construct the inherited object, clear the stored state fields, install its derived vtable, and return the receiver.
// Reference algorithm: src/hand/func_00146EE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_003636D0[];
struct S { char unknown_0[0xC]; void * vtable; char unknown_10[0x538]; int value_548; };
struct S *func_002B5898(struct S *object);
struct S *func_002B7A78(struct S *object)
{
    func_002B5898(object);
    object->value_548 = 0;
    object->vtable = D_003636D0;
    return object;
}
