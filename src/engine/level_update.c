// SLY3_CFLAGS: -Os -G0
struct EngineLevelItem { unsigned char prefix[0xA4]; int value; };
struct EngineLevelHolder { unsigned char prefix[0x40]; struct EngineLevelItem *item; };
struct EngineLevelEntry { short delta,padding; struct EngineLevelHolder *(*fn)(void *); };
struct EngineLevelOwner { unsigned char prefix[0x14]; struct EngineLevelEntry *table; int level; };
extern unsigned char D_00475480[];
void func_0015B6B0(void *game,void *owner);
void func_0015CE68(struct EngineLevelOwner *owner)
{
    struct EngineLevelItem *item=owner->table[1].fn((char *)owner+owner->table[1].delta)->item;
    int value=0;
    if(item) value=item->value;
    if(owner->level<value) {
        owner->level=value;
        func_0015B6B0(D_00475480,owner);
    }
}
