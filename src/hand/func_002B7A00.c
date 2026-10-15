// Construct the inherited object, clear the stored state fields, install its derived vtable, and return the receiver.
// Reference algorithm: src/hand/func_0013CEF8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0036A2E0[];
struct S { char unknown_0[0xC]; void * vtable; char unknown_10[0x2A4]; int value_2B4; char unknown_2B8[0x124]; int value_3DC; };
struct S *func_002B5898(struct S *object);
struct S *func_002B7A00(struct S *object)
{
    func_002B5898(object);
    object->value_2B4 = 0;
    object->value_3DC = 0;
    object->vtable = D_0036A2E0;
    return object;
}
