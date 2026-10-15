// Install the original vtable at object offset0xEC and return the explicit receiver.
// Reference algorithm: src/hand/func_001F5860.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00354E58[];
struct S { char unknown_0[0xEC]; void * vtable; };
struct S *func_002B8848(struct S *object)
{
    object->vtable=D_00354E58;
    return object;
}
