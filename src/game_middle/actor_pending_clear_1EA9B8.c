// SLY3_CFLAGS: -Os -G0
struct PendingActor {
    char unknown00[0x16A8];
    int state;
    char unknown16AC[0x16E4 - 0x16AC];
    int count;
    int unknown16E8;
    int pending;
};
void func_001EA4B0(void *receiver, int state);
void func_001EA9B8(void *receiver)
{
    struct PendingActor *actor = (struct PendingActor *)receiver;
    actor->pending = 0;
    switch (actor->state) {
    case 0:
    case 1:
        if (actor->count > 0)
            func_001EA4B0(receiver, 2);
        break;
    }
}
