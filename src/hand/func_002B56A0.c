// Construct the inherited object, install its derived vtable, initialize the embedded record, and return the receiver.
// Reference algorithm: src/hand/func_001DFFE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00365968[];
struct S { char unknown_0[0xC]; void * vtable; };
struct S *func_002B52F0(struct S *object);
void *func_0018D138(void *record);
struct S *func_002B56A0(struct S *object)
{
    func_002B52F0(object);
    object->vtable=D_00365968;
    func_0018D138((char *)object+0x70);
    return object;
}
