// SLY3_CFLAGS: -Os -G0 -fno-exceptions
union EntryFlags {
    unsigned long value;
    struct {
        unsigned long low:16;
        unsigned long flag:1;
        unsigned long rest:47;
    } __attribute__((packed)) fields;
} __attribute__((packed,aligned(8)));
struct FlagEntry { unsigned char prefix[0x18]; EntryFlags flags; unsigned char rest[0xD0-0x20]; };
struct FlagOwner { unsigned char prefix[0xD0]; int count; FlagEntry *entries; };
extern "C" void func_0023FCD8(FlagOwner *owner,int value)
{
    for(int i=0;i<owner->count;i++)
        owner->entries[i].flags.fields.flag=value;
}
