// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t,dt; };
extern struct CLOCK D_0036BB98;
struct EngineExpireEntry { short delta,padding; void (*fn)(void *); };
struct EngineExpireItem { unsigned char prefix[0xC]; struct EngineExpireEntry *table; unsigned char gap[0x28-0x10]; unsigned long flags; };
struct EngineExpireSlot { struct EngineExpireItem *item; float time; };
struct EngineExpireOwner { unsigned char prefix[0x360]; struct EngineExpireSlot slots[4]; };
void func_00145ED8(struct EngineExpireOwner *owner)
{
    unsigned int i;
    for(i=0;i<4;i++) {
        struct EngineExpireSlot *slot=&owner->slots[i];
        struct EngineExpireItem *item=slot->item;
        if(item) {
            int flagged=(item->flags&(1UL<<56))!=0;
            if(flagged) {
                if(D_0036BB98.t-slot->time>3.0f) item->table[9].fn((char *)item+item->table[9].delta);
            }
        }
    }
}
