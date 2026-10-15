// Filter the receiver by its enabled state, optional peer and optional attached-record state.
// Complete original inputs, boundaries and initialized sections are independently reviewed.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int FLAGS64 __attribute__((mode(DI)));
struct Attached {
    char prefix[0x44];
    int state;
};
struct Receiver {
    char prefix[0x28];
    FLAGS64 flags;
    char gap30[0xAC];
    struct Attached *attached;
    char gapE0[0x10];
    struct Receiver *peer;
};
int func_0024D6E8(struct Receiver *p)
{
    if (!((int)(p->flags >> 56) & 1))
        return 0;
    if (p->peer && ((int)(p->peer->flags >> 56) & 1))
        return 0;
    if (p->attached && p->attached->state != 1)
        return 0;
    return 1;
}
