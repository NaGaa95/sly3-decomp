// Mark the selection absent, disable the object, and clear its flags.
// Reference algorithm: src/hand/func_001A5BF0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { int reserved; int selection; int reserved2; int flags; };
void func_00259CA8(struct S *object,int enabled);
void func_00259A08(struct S *object)
{
    object->selection=-1;
    func_00259CA8(object,0);
    object->flags=0;
}
