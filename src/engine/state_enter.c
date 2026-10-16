// SLY3_CFLAGS: -Os -G0
struct EngineStateTarget;
struct EngineStateTargetEntry { short delta,padding; void (*fn)(void *,int,int,int,int,int); };
struct EngineStateTarget { unsigned char prefix[0xC]; struct EngineStateTargetEntry *table; };
struct EngineStateOwnerEntry { short delta,padding; struct EngineStateTarget *(*fn)(void *); };
struct EngineStateOwner { unsigned char prefix[0xEC]; struct EngineStateOwnerEntry *table; };
void func_0015BFF8(struct EngineStateOwner *owner,int flag);
void func_0015BF28(struct EngineStateOwner *owner)
{
    struct EngineStateTarget *target=owner->table[1].fn((char *)owner+owner->table[1].delta);
    target->table[3].fn((char *)target+target->table[3].delta,5,0,0,0,0);
    func_0015BFF8(owner,1);
}
