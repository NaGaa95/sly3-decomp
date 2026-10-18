// SLY3_CFLAGS: -Os -G0
struct Entry { int handle; unsigned char gap4[0x10]; };
struct Item { unsigned char prefix[0x28]; int count; struct Entry entries[1]; };
void func_0028A818(void *manager,int handle);
void *func_00291F38(void *dest,const void *src,unsigned size);
static inline void MoveEntries(struct Entry *dest,struct Entry *src,unsigned size)
{
    func_00291F38(dest,src,size);
}
void func_0028AD48(void *manager,struct Item *item,int index)
{
    func_0028A818(manager,item->entries[index].handle);
    MoveEntries(&item->entries[index],&item->entries[index+1],(item->count-index)*sizeof(struct Entry)-sizeof(struct Entry));
    item->count--;
}
