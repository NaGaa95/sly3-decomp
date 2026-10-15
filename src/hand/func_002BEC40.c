// Install the original vtable at object offset0xE8 and return the explicit receiver.
// Reference algorithm: src/hand/func_001F5860.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_003621A0[];
struct S { char unknown_0[0xE8]; void * vtable; };
struct S *func_002BEC40(struct S *object)
{
    object->vtable=D_003621A0;
    return object;
}
