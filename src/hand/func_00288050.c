// Update the inherited object, invoke its original cleanup virtual method, and apply the stored record value.
// Reference algorithm: src/hand/func_001D4EC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct PMF { short adjustment;short reserved;void (*method)(void *); };
struct R { char prefix[0x208]; int value; };
struct S { char unknown_0[0xC]; struct PMF * vtable; char unknown_10[0x154]; struct R * record; };
void func_00287F48(struct S *object);
void func_001C8FB0(struct S *object,int value);
void func_00288050(struct S *object)
{
    struct PMF *slot;
    func_00287F48(object);
    slot=object->vtable+9;slot->method((char *)object+slot->adjustment);
    func_001C8FB0(object,object->record->value);
}
