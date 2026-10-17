// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t,dt; };
extern struct CLOCK D_0036BB98;
struct StampEntry { short delta,padding; void (*fn)(void *); };
struct StampObject { unsigned char prefix[0xC]; struct StampEntry *table; unsigned char gap10[0x28-0x10]; unsigned long flags; unsigned char gap30[0x58-0x30]; float stamp; };
void func_0017D7D0(struct StampObject *object)
{
    int flagged=(object->flags&(1UL<<56))!=0;
    if(!flagged) {
        object->stamp=D_0036BB98.t;
        object->table[8].fn((char *)object+object->table[8].delta);
    }
}
