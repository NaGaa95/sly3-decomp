// Construct the inherited object and install both the embedded interface table and derived object vtable.
// Reference algorithm: src/hand/func_0015CD68.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00354688[], D_003546C8[];
struct S { char unknown_0[0xC]; void * vtable; char unknown_10[0x20C]; void * interface; };
struct S *func_002B6060(struct S *object);
struct S *func_002B6108(struct S *object)
{
    func_002B6060(object);
    object->interface = D_00354688;
    object->vtable = D_003546C8;
    return object;
}
