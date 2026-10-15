// Install the original vtable at object offset0x0 and return the explicit receiver.
// Reference algorithm: src/hand/func_001F5860.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00366D58[];
struct S { void * vtable; };
struct S *func_002BF768(struct S *object)
{
    object->vtable=D_00366D58;
    return object;
}
