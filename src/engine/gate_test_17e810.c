// SLY3_CFLAGS: -Os -G0
struct GateTarget { unsigned char prefix[0x40C]; int mode; unsigned char gap[0x4A4-0x410]; int pending; };
struct GateOwner { unsigned char prefix[0x11B4]; struct GateTarget *target; unsigned char gap[0x11BC-0x11B8]; int state; };
struct GateHolder { struct GateOwner *owner; };

int func_0017E810(struct GateHolder *holder)
{
    struct GateOwner *owner=holder->owner;
    struct GateTarget *target;
    if(owner->state!=3) { zero: return 0; }
    target=owner->target;
    if(target->mode!=2) goto zero;
    if(target->pending!=0) goto zero;
    return 1;
}
