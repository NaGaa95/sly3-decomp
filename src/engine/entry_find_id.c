// SLY3_CFLAGS: -Os -G0
struct IdEntry { unsigned char prefix[0xE0]; int id; unsigned char tail[0xF0-0xE4]; };
struct IdOwner { unsigned char prefix[0x5C]; int count; struct IdEntry *entries; };
struct IdEntry *func_00172A90(struct IdOwner *owner,int id)
{
    int i;
    if(id==-1) return 0;
    for(i=0;i<owner->count;i++) {
        struct IdEntry *entry=&owner->entries[i];
        if(entry->id==id) return entry;
    }
    return 0;
}
