// Construct the original inherited object and install its three interface/vtable pointers.
// Reference algorithm: src/hand/func_00179598.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0035A950[];
extern char D_0035A990[];
extern char D_0035A788[];
struct S { char unknown_0[0xC]; void * table_C; char unknown_10[0xE4]; void * table_F4; char unknown_F8[0x14]; void * table_10C; };
struct S *func_002B67D0(struct S *object);
struct S *func_002B6830(struct S *object)
{
    func_002B67D0(object);
    object->table_F4=D_0035A950;
    object->table_10C=D_0035A990;
    object->table_C=D_0035A788;
    return object;
}
