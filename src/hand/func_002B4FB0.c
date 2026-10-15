// Construct the inherited object, clear the stored state fields, install its derived vtable, and return the receiver.
// Reference algorithm: src/hand/func_00146EE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0034E620[];
struct S { void * vtable; char unknown_4[0xC]; int value_10; };
struct S *func_002B4F98(struct S *object);
struct S *func_002B4FB0(struct S *object)
{
    func_002B4F98(object);
    object->value_10 = 0;
    object->vtable = D_0034E620;
    return object;
}
