// SLY3_CFLAGS: -Os -G0
typedef int PackedActorDefaults __attribute__((mode(TI)));
struct ActorDefaultRange { float lower, upper; };
struct ActorPackedResetView {
    char prefix[0x3C];
    unsigned int tagged_flags;
    char unaccessed40[0x1B0-0x40];
    PackedActorDefaults defaults;
    struct ActorDefaultRange range;
    char unaccessed1C8[8];
    int reset1D0;
    int unaccessed1D4;
    float value1D8;
    float value1DC;
};
extern PackedActorDefaults D_00321F20;
extern struct ActorDefaultRange D_00321F30;
void func_001F3B50(void *receiver);
void func_001F43F8(void *receiver, int value);

void func_0019B420(struct ActorPackedResetView *p)
{
    unsigned int flags;
    func_001F3B50(p);
    func_001F43F8(p, 10);
    p->reset1D0 = -1;
    p->value1D8 = 20.0f;
    p->value1DC = 1000.0f;
    p->defaults = D_00321F20;
    p->range = D_00321F30;
    flags = p->tagged_flags;
    if ((flags ^ 1) & 1)
        *(unsigned int *)flags |= 2;
    else
        p->tagged_flags = flags | 2;
}
