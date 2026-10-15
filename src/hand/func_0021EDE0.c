// Construct the inherited object, install its derived vtable, initialize its state, and return the receiver.
// Reference algorithm: src/hand/func_001DFFE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00363E60[];
struct S { char prefix[0xC]; void *vtable; };
struct S *func_0021EB00(struct S *object);
void func_0021EE50(struct S *object);
struct S *func_0021EDE0(struct S *object)
{
    func_0021EB00(object);
    object->vtable=D_00363E60;
    func_0021EE50(object);
    return object;
}
