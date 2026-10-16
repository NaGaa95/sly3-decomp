// SLY3_CFLAGS: -Os -G0
struct EnginePickSub { unsigned char prefix[0x20]; int first; unsigned char gap[4]; int second; };
struct EnginePickOwner { unsigned char prefix[0x44]; int fallback; unsigned char gap[0x54-0x48]; int selector; struct EnginePickSub *sub; };
int func_001733C8(struct EnginePickOwner *owner)
{
    struct EnginePickSub *sub=owner->sub;
    int value=0;
    if(sub) value=owner->selector==0?sub->second:sub->first;
    if(!value) value=owner->fallback;
    return value;
}
