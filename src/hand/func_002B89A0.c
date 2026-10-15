// Install the original vtable at object offset0x2C and return the explicit receiver.
// Reference algorithm: src/hand/func_001F5860.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0035BBD8[];
struct S { char unknown_0[0x2C]; void * vtable; };
struct S *func_002B89A0(struct S *object)
{
    object->vtable=D_0035BBD8;
    return object;
}
