// Invoke the stored owner cleanup method through its adjusted virtual slot and unlink the receiver.
// Reference algorithm: src/hand/func_0014F6F0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct PMF { short adjustment; short reserved; void (*method)(void *); };
struct O { char prefix[0xC]; struct PMF *vtable; };
struct S { char prefix[0x1C]; struct O *owner; };
void func_0020BD70(struct S *object);
void func_0020D710(struct S *object)
{
    struct O *owner=object->owner;
    struct PMF *slot=owner->vtable+8;
    slot->method((char *)owner+slot->adjustment);
    func_0020BD70(object);
}
