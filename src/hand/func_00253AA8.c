// Run the original resource update only when bit59 of the stored64-bit flags is set.
// Reference algorithm: src/hand/func_00203758.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int U64 __attribute__((mode(DI)));
struct S { char prefix[0x28]; U64 flags; };
void func_00253AE0(struct S *object);
void func_00253AA8(struct S *object)
{
    if(object->flags & ((U64)0x8000<<44))func_00253AE0(object);
}
