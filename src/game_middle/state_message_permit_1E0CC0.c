// SLY3_CFLAGS: -Os -G0
struct PermitActor {
    unsigned char prefix[0x1520];
    int state;
};
int func_001B5DD8(void *context, int ignored_event);
int func_00153668(void *receiver, int message);
int func_001E0CC0(struct PermitActor *actor, int message)
{
    switch (actor->state) {
    case 0x10:
    case 0x17:
        return 1;
    case 0x15:
        if (message == 0x4000)
            return 1;
        break;
    case 0xE:
        if (func_001B5DD8((char *)actor + 0x500, message))
            return 1;
        break;
    }
    return func_00153668(actor, message);
}
