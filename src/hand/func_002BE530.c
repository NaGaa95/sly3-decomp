// Apply the original initialization and state table, then set the stored initialization flag.
// Reference algorithm: src/hand/func_002079A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0036AE38[];
struct S { int reserved; unsigned int flags; };
void func_002B4308(struct S *object);
void func_002B41C8(struct S *object,void *table);
void func_002BE530(struct S *object)
{
    func_002B4308(object);
    func_002B41C8(object,D_0036AE38);
    object->flags |= 0x8000;
}
