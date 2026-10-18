// SLY3_CFLAGS: -Os -G0
struct Entry { void *object; int first; int second; };
struct VirtualEntry { short delta,reserved; void (*call)(void *,int,int); };
struct Object { unsigned char prefix[0xC]; struct VirtualEntry *table; };
struct Owner { unsigned char prefix[0x98]; int count; struct Entry entries[1]; };
int func_0013B500(void *object,int kind);
void *func_00291F38(void *destination,void *source,int bytes);
static inline void MoveEntries(struct Entry *dest,struct Entry *src,unsigned size)
{
    func_00291F38(dest,src,size);
}
void func_0022B580(struct Owner *owner,struct Object *object,int first,int second)
{
    int index;
    if(!func_0013B500(object,0x32))
        return;
    for(index=0;index<owner->count;index++)
        if(owner->entries[index].object==object)
            break;
    if(index<owner->count) {
        struct VirtualEntry *entry;
        MoveEntries(&owner->entries[index],&owner->entries[index+1],(owner->count-index)*12-12);
        owner->count--;
        entry=&object->table[95];
        entry->call((char *)object+entry->delta,first,second);
    }
}
