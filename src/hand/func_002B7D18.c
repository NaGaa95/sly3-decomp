// Construct the inherited object, install its derived vtable, initialize the embedded record, and return the receiver.
// Reference algorithm: src/hand/func_001DFFE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00357B20[];
struct S { char unknown_0[0xC]; void * vtable; };
struct S *func_002606A0(struct S *object);
void *func_002B4FB0(void *record);
struct S *func_002B7D18(struct S *object)
{
    func_002606A0(object);
    object->vtable=D_00357B20;
    func_002B4FB0((char *)object+0x1D4);
    return object;
}
