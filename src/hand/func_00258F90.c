// Reset the inherited object, invoke its adjusted virtual cleanup method, and complete the receiver cleanup.
// Reference algorithm: src/hand/func_001492B0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct PMF { short adjustment; short unused; void (*method)(void *); };
struct S { char prefix[0xC]; struct PMF *vtable; };
void func_001C7DC8(struct S *object);
void func_00258FD0(struct S *object);
void func_00258F90(struct S *object)
{
    struct PMF *slot;
    func_001C7DC8(object);
    slot = object->vtable + 9;
    slot->method((char *)object + slot->adjustment);
    func_00258FD0(object);
}
