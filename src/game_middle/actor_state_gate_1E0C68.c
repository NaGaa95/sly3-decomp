// SLY3_CFLAGS: -Os -G0
struct StateGateView {
    unsigned char prefix[0x214];
    int blocked;
    unsigned char gap218[0x1520 - 0x218];
    int state;
    unsigned char gap1524[4];
    int mode;
};
int func_00156388(void *actor);
int func_001E0C68(struct StateGateView *actor)
{
    if (actor->blocked || actor->mode == 1 || actor->state == 0x15 || actor->state == 0x16)
        return 0;
    return func_00156388(actor);
}
