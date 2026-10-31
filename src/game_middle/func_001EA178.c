// SLY3_CFLAGS: -Os -G0
struct ModeActor {
    unsigned char prefix[0x1470];
    int state;
};
void func_00155CE0(void *actor);
int func_001EA940(void *actor);
void func_001EA4B0(void *actor, int state);

void func_001EA178(struct ModeActor *actor)
{
    func_00155CE0(actor);
    func_001EA4B0(actor, func_001EA940(actor) ? 2 : -1);
}

int func_001EA1B8(struct ModeActor *actor)
{
    int state = actor->state;
    if (state < 4) {
        if (state >= 0)
            return 1;
    }
    return 0;
}
