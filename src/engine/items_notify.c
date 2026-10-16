// SLY3_CFLAGS: -Os -G0
struct EngineNotifyEntry { short delta,padding; void (*fn)(void *); };
struct EngineNotifyItem { unsigned char prefix[0xC]; struct EngineNotifyEntry *table; };
struct EngineNotifyOwner { unsigned char prefix[0x314]; int count; struct EngineNotifyItem *items[1]; unsigned char gap[0x410-0x31C]; int mode; };
void func_00145E40(struct EngineNotifyOwner *owner)
{
    int i;
    for(i=0;i<owner->count;i++) {
        struct EngineNotifyItem *item=owner->items[i];
        if(item) {
            if(owner->mode) item->table[8].fn((char *)item+item->table[8].delta);
            else item->table[9].fn((char *)item+item->table[9].delta);
        }
    }
}
