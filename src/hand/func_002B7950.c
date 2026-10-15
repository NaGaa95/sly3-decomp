// Construct the inherited object, clear the stored state fields, install its derived vtable, and return the receiver.
// Reference algorithm: src/hand/func_0013CEF8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00361860[];
struct S { char unknown_0[0xC]; void * vtable; char unknown_10[0x3D8]; int value_3E8; char unknown_3EC[0x8]; int value_3F4; };
struct S *func_002B5898(struct S *object);
struct S *func_002B7950(struct S *object)
{
    func_002B5898(object);
    object->value_3E8 = 0;
    object->value_3F4 = 0;
    object->vtable = D_00361860;
    return object;
}
