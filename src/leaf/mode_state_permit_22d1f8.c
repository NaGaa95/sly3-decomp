// SLY3_CFLAGS: -Os -G0
// Mode gate: the base check passes, then states 3 and 4 delegate to their sub-objects; only modes 2 and 3 are permitted.
struct PermitActor {
    unsigned char prefix[0x1470];
    int state;
};
int func_00154518(void *receiver, int mode);
int func_001BD830(void *context, int mode);
int func_001B5D08(void *context, int mode);
int func_0022D1F8(struct PermitActor *actor, int mode)
{
    if (!func_00154518(actor, mode))
        return 0;
    switch (actor->state) {
    case 3:
        if (!func_001BD830((char *)actor + 0x320, mode))
            return 0;
        break;
    case 4:
        if (!func_001B5D08((char *)actor + 0x500, mode))
            return 0;
        break;
    case 0:
    case 1:
    case 2:
        break;
    default:
        return 0;
    }
    switch (mode) {
    default:
        return 0;
    case 2:
    case 3:
        return 1;
    }
}
