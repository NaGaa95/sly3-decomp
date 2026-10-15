// Construct the original inherited object and install its three interface/vtable pointers.
// Reference algorithm: src/hand/func_00179598.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00354958[];
extern char D_00354998[];
extern char D_00369518[];
struct S { char unknown_0[0xC]; void * table_C; char unknown_10[0x1FC]; void * table_20C; char unknown_210[0x14]; void * table_224; };
struct S *func_002B60A8(struct S *object);
struct S *func_002B6148(struct S *object)
{
    func_002B60A8(object);
    object->table_20C=D_00354958;
    object->table_224=D_00354998;
    object->table_C=D_00369518;
    return object;
}
