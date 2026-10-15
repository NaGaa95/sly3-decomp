// Clear the explicit object value only when the owner64-bit flags contain bit five.
// Reference algorithm: src/hand/func_00221120.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int U64 __attribute__((mode(DI)));
struct O { char prefix[0x128]; U64 flags; };
struct S { char prefix[0x94]; int value; };
void func_0023E110(struct O *owner,struct S *object)
{
    if(owner->flags & 0x20)object->value=0;
}
