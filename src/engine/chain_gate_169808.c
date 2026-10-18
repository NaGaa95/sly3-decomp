// SLY3_CFLAGS: -Os -G0
int func_0013B500(void *object, int kind);
struct ChainEntry { short delta, padding; int (*fn)(void *, int); };
struct ChainObject { unsigned char prefix[0xC]; struct ChainEntry *table; };
int func_00169808(struct ChainObject *object)
{
    if(!object) return 0;
    if(func_0013B500(object, 0x33)) {
        struct ChainEntry *entry = &object->table[120];
        if(entry->fn((char *)object + entry->delta, 0)) return 1;
    }
    return 0;
}
