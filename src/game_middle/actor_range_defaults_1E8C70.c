// SLY3_CFLAGS: -Os -G0
struct RangeDefaultsView {
    char prefix[0x3C];
    unsigned int tagged_flags;
    char gap40[0x194 - 0x40];
    int marker;
    char gap198[0x1A4 - 0x198];
    float lowA, highA;
    float lowB, highB;
    char gap1B4[4];
    float limit;
};
void func_001F3B50(void *receiver);
void func_001E8C70(struct RangeDefaultsView *p)
{
    unsigned int flags;
    func_001F3B50(p);
    flags = p->tagged_flags;
    p->lowA = -1.0f;
    p->highA = 1.0f;
    p->lowB = -1.0f;
    p->highB = 1.0f;
    p->limit = 2.5f;
    p->marker = -1;
    if ((flags ^ 1) & 1)
        *(unsigned int *)flags |= 2;
    else
        p->tagged_flags = flags | 2;
}
