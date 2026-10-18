// SLY3_CFLAGS: -Os -G0
struct AllocationRequest { int bytes, alignment; };
struct EntryRecord {
    int key;
    void *object;
    int unused;
};
struct EntryOwner {
    unsigned char prefix[0x3C];
    int flags;
    int count;
    struct EntryRecord *entries;
    unsigned char gap48[4];
    int recordCount;
    void *buffer;
};
extern unsigned char D_00475480[];
void func_001C7DC8(void *owner);
void *func_0017E1B8(void *game, int flags, int key, void *owner);
void *func_001D2538(struct AllocationRequest *request);
void func_001C9118(void *owner, int mode);
void func_0021AA68(struct EntryOwner *owner)
{
    struct AllocationRequest request;
    int i;
    func_001C7DC8(owner);
    for (i = 0; i < owner->count; i++) {
        struct EntryRecord *entry = &owner->entries[i];
        entry->object = func_0017E1B8(D_00475480, 5, entry->key, 0);
    }
    request.bytes = owner->recordCount * 12;
    request.alignment = 0x10;
    owner->buffer = func_001D2538(&request);
    func_001C9118(owner, 1);
    {
        int tagged = owner->flags;
        if ((tagged ^ 1) & 1)
            *(int *)tagged |= 2;
        else
            owner->flags = tagged | 2;
    }
}
