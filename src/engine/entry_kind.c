// SLY3_CFLAGS: -Os -G0
struct EngineKindEntry { unsigned char prefix[0x30]; int kind; };
struct EngineKindOwner { unsigned char prefix[0x29C]; unsigned char list[1]; };
struct EngineKindEntry *func_002387A8(void *list,int key);
int func_00252408(void *owner,int value);
int func_00161B78(struct EngineKindOwner *owner,int value)
{
    struct EngineKindEntry *entry=func_002387A8(owner->list,0xE9);
    if(entry && (entry->kind==0x11 || entry->kind==0x14)) return 1;
    return func_00252408(owner,value);
}
