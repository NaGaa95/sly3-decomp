// SLY3_CFLAGS: -Os -G0
struct Player { unsigned char storage[0x11C0]; };
extern struct Player D_0036E740[];
struct SwapEntry { short delta,padding; void (*fn)(void *); };
struct SwapTarget { unsigned char prefix[0x1C]; struct SwapEntry *table; };
struct SwapOwner { unsigned char prefix[0xD0]; int player; unsigned char gapD4[0x300-0xD4]; struct SwapTarget *target; };
int func_00165DC8(void *owner);
void func_001A9240(void *player,void *owner);
void func_001A91E0(void *player,void *owner);
void func_001685C8(void *owner);
void func_00168478(struct SwapOwner *owner,int player)
{
    struct SwapTarget *old;
    if(player==owner->player) return;
    if(func_00165DC8(owner)) { owner->player=player; return; }
    old=owner->target;
    if(old) old->table[2].fn((char *)old+old->table[2].delta);
    if(owner->player!=-1) func_001A9240(owner->player+D_0036E740,owner);
    owner->player=player;
    if(player!=-1) func_001A91E0(player+D_0036E740,owner);
    if(old) old->table[1].fn((char *)old+old->table[1].delta);
    func_001685C8(owner);
}
