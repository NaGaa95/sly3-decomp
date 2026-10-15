// Construct the inherited object and install both the embedded interface table and derived object vtable.
// Reference algorithm: src/hand/func_0015CD68.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00353CC0[], D_003646C8[];
struct S { char unknown_0[0xC]; void * vtable; char unknown_10[0x304]; void * interface; };
struct S *func_002B88B0(struct S *object);
struct S *func_002B6E88(struct S *object)
{
    func_002B88B0(object);
    object->interface = D_00353CC0;
    object->vtable = D_003646C8;
    return object;
}
