// SLY3_CFLAGS: -Os -G0
struct RecordFlags { unsigned char opaque00[0x18]; unsigned long flags; unsigned char opaque20[0xD0 - 0x20]; };
struct RecordOwner { unsigned char opaque[0xD0]; int count; struct RecordFlags *records; };
void func_0023C0B8(void *owner);
void func_001DC6F8(void *receiver)
{
    struct RecordOwner *owner = (struct RecordOwner *)receiver;
    int index;
    func_0023C0B8(receiver);
    for (index = 0; index < owner->count; index++) {
        struct RecordFlags *record = &owner->records[index];
        if (!(record->flags & 0x20000))
            record->flags |= 0x40000;
    }
}
