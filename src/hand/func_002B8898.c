// Install the original vtable at object offset0x24 and return the explicit receiver.
// Reference algorithm: src/hand/func_001F5860.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0035B4E8[];
struct S { char unknown_0[0x24]; void * vtable; };
struct S *func_002B8898(struct S *object)
{
    object->vtable=D_0035B4E8;
    return object;
}
