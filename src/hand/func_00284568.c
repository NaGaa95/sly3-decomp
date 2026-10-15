// Disable the receiver and invoke the stored owner reset virtual method when present.
// Reference algorithm: src/hand/func_00179820.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct PMF { short adjustment; short reserved; void (*method)(void *); };
struct O { char prefix[0xC]; struct PMF *vtable; };
struct S { char prefix[0x18]; struct O *owner; };
void func_00284DC8(struct S *object,int enabled);
void func_00284568(struct S *object)
{
    struct O *owner;
    func_00284DC8(object,0);
    owner=object->owner;
    if(owner){struct PMF *slot=owner->vtable+54;slot->method((char *)owner+slot->adjustment);}
}
