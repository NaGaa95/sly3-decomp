// SLY3_CFLAGS: -Os -G0
struct EngineShutdownEntry { short delta,padding; void (*fn)(void *); };
struct EngineShutdownChild { unsigned char prefix[0xC]; struct EngineShutdownEntry *table; };
struct EngineShutdownMarker { unsigned char prefix[0x19C]; int state; };
struct EngineShutdownOwner { unsigned char prefix[0x17E8]; struct EngineShutdownMarker *marker; unsigned char gap[0x1880-0x17EC]; struct EngineShutdownChild *child; };
void func_00250E38(void *owner);
int func_001F4458(void *owner);
void func_001F4438(void *owner,int value);
void func_00251A58(void *owner,int flag);
void func_0015F528(struct EngineShutdownOwner *owner)
{
    func_00250E38(owner);
    func_001F4438(owner,func_001F4458(owner));
    func_00251A58(owner,1);
    if(owner->child) owner->child->table[9].fn((char *)owner->child+owner->child->table[9].delta);
    if(owner->marker) owner->marker->state=4;
}
