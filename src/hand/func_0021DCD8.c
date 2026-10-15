// Construct the inherited object and initialize the derived vtable, absent selection and high flag bit.
// Reference algorithm: src/hand/func_0013CFD8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00363F60[];
struct S { char unknown_0[0xC]; void * vtable; char unknown_10[0x8]; int selection; char unknown_1C[0x4]; unsigned int flags; };
struct S *func_002B8670(struct S *object);
struct S *func_0021DCD8(struct S *object)
{
    func_002B8670(object);
    object->vtable=D_00363F60;
    object->selection=-1;
    object->flags=0x80000000u;
    return object;
}
