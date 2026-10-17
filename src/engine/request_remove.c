// SLY3_CFLAGS: -Os -G0
struct RequestEntry { int words[5]; };
struct RequestOwner { unsigned char prefix[0xD8]; int count; struct RequestEntry entries[1]; };
struct RequestEntry *func_00170528(struct RequestOwner *owner);
void func_00170410(struct RequestOwner *owner,struct RequestEntry *entry,int mode);
void *func_00291F38(void *destination,void *source,int bytes);
void func_001702A0(struct RequestOwner *owner)
{
    struct RequestEntry *entry=func_00170528(owner);
    if(entry) {
        func_00170410(owner,entry,0);
        owner->count--;
        func_00291F38(entry,entry+1,(&owner->entries[owner->count]-entry)*sizeof(struct RequestEntry));
    }
}
