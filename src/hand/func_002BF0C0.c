// Construct the inherited object, clear the stored state fields, install its derived vtable, and return the receiver.
// Reference algorithm: src/hand/func_0013CEF8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_003644D8[];
struct S { char unknown_0[0xC]; void * vtable; char unknown_10[0x8]; int value_18; char unknown_1C[0xF8]; int value_114; };
struct S *func_002B8670(struct S *object);
struct S *func_002BF0C0(struct S *object)
{
    func_002B8670(object);
    object->value_18 = 0;
    object->value_114 = 0;
    object->vtable = D_003644D8;
    return object;
}
