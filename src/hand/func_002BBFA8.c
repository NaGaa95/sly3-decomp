// Apply the original initialization and state table, then set the stored initialization flag.
// Reference algorithm: src/hand/func_002079A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0036AE60[];
struct S { int reserved; unsigned int flags; };
void func_002B4A88(struct S *object);
void func_002B4948(struct S *object,void *table);
void func_002BBFA8(struct S *object)
{
    func_002B4A88(object);
    func_002B4948(object,D_0036AE60);
    object->flags |= 0x8000;
}
