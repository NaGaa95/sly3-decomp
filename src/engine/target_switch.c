// SLY3_CFLAGS: -Os -G0
struct Player { unsigned char prefix[0x110C]; void *target; unsigned char tail[0x11C0-0x1110]; };
extern struct Player D_0036E740[];
struct TargetEntry { short delta,padding; void *(*fn)(void *,void *); };
struct TargetObject { unsigned char prefix[0xC]; struct TargetEntry *table; };
struct TargetOwner { unsigned char prefix[0xD0]; int player; unsigned char padD4[0xDC-0xD4]; struct TargetObject *forced; struct TargetObject *current; void *handle; unsigned char padE8[0x414-0xE8]; int word414; };
void func_00169C40(void *handle);
void func_00169CE0(void *handle);
void func_001685C8(struct TargetOwner *owner)
{
    struct TargetObject *target;
    if(owner->forced) target=owner->forced;
    else if(owner->player!=-1) target=(struct TargetObject *)(owner->player+D_0036E740)->target;
    else target=0;
    if(target!=owner->current) {
        func_00169C40(&owner->handle);
        owner->current=target;
        owner->word414=0;
        if(target) {
            owner->handle=target->table[82].fn((char *)target+target->table[82].delta,owner);
            func_00169CE0(owner->handle);
        }
    }
}
