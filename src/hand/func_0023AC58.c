// Release the owned object through its original cleanup and adjusted virtual destructor, then clear the ownership pointer.
// Reference algorithm: src/hand/func_001E5410.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct PMF { short adjustment; short reserved; void (*method)(void *); };
struct O { char prefix[0xC]; struct PMF *vtable; };
struct S { struct O *object; };
void func_00239C20(struct O *object);
void func_0023AC58(struct S *record)
{
    if(record->object){
        struct O *object;struct PMF *slot;
        func_00239C20(record->object);
        object=record->object;slot=object->vtable+2;
        slot->method((char *)object+slot->adjustment);
        record->object=0;
    }
}
