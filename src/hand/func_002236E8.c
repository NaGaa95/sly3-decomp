// Apply the inherited update and set bit two in the original64-bit flag word.
// Reference algorithm: src/hand/func_00182E80.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int U64 __attribute__((mode(DI)));
struct S { char prefix[0x128]; U64 flags; };
void func_0023AE08(struct S *object);
void func_002236E8(struct S *object)
{
    func_0023AE08(object);
    object->flags |= 4;
}
