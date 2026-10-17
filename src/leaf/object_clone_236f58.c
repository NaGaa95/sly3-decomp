// SLY3_CFLAGS: -Os -G0
struct Entry { short delta,padding; void *(*fn)(void *); };
struct Template { unsigned char prefix[0xC]; unsigned int size; void *(*create)(void); };
struct Source { unsigned char prefix[0xC]; struct Entry *table; };
extern char D_00479DA4[];
void func_001D2898(void *destination,void *source,unsigned int bytes);
void func_0011AD70(void *object);
void func_0011AD68(void *object);
void func_0011AD80(void *list,void *object);
void *func_00236F58(struct Source *source)
{
    struct Entry *entry=&source->table[6];
    struct Template *template=entry->fn((char *)source+entry->delta);
    void *copy=template->create();
    func_001D2898(copy,source,template->size);
    func_0011AD70((char *)copy+0x38);
    func_0011AD68((char *)copy+0x44);
    func_0011AD80(D_00479DA4,copy);
    return copy;
}
