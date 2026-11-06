// SLY3_CFLAGS: -Os -G0
// Mode permission test of an actor: shared checks first, then a per-state check (some states delegate to a sub-context),
// then a per-mode answer. Same family as func_001EA1E0.
struct PermitActor {
    unsigned char prefix000[0x21C];
    float x21C;
    unsigned char gap220[0x324 - 0x220];
    int x324;
    unsigned char gap328[0x1108 - 0x328];
    void *x1108;
    unsigned char gap110C[0x1520 - 0x110C];
    unsigned int state;
    unsigned char gap1524[0x1540 - 0x1524];
    struct { unsigned char pad[0x190]; void *x190; } *x1540;
    unsigned char gap1544[0x1AD4 - 0x1544];
    int x1AD4;
    float x1AD8;
    unsigned char gap1ADC[0x1C9C - 0x1ADC];
    int x1C9C;
};
int func_00154518(void *receiver, int mode);
int func_00173428(void *object);
int func_001BD830(void *context, int mode);
int func_001B5D08(void *context, int mode);
int func_001BFFB8(void *context, int mode);
int func_0013B500(void *object, int key);
static inline int HasHeldObject(struct PermitActor *actor)
{
    int held = 0;
    if (actor->x1108)
        held = func_00173428(actor->x1108) != 0;
    return held;
}
int func_001E23F0(struct PermitActor *actor, int mode)
{
    if (!func_00154518(actor, mode))
        return 0;
    if (mode != 3 && HasHeldObject(actor))
        return 0;
    if (mode == 0x13)
        return 1;
    switch (actor->state) {
    default:
        return 0;
    case 2:
        if (!func_001BD830((char *)actor + 0x320, mode))
            return 0;
        break;
    case 14:
        if (!func_001B5D08((char *)actor + 0x500, mode))
            return 0;
        break;
    case 21:
        if (!func_001BFFB8((char *)actor + 0x1010, mode))
            return 0;
        break;
    case 22:
        return mode == 0x11;
    case 5:
        if (mode == 3)
            return 1;
        if (mode == 0x18) {
            if (func_0013B500(actor->x1540->x190, 0x3A))
                return 1;
        }
        return 0;
    case 0: case 1: case 10: case 11:
        break;
    }
    switch (mode) {
    default:
        return 0;
    case 22:
        if (actor->x1C9C)
            return 0;
        break;
    case 23: {
        int result = 0;
        if (actor->x324 != 0 && actor->x324 != 0xB)
            result = actor->x324 != -1;
        return result;
    }
    case 17: {
        int result = 0;
        if (actor->x1AD4 == -1) {
            if (actor->x21C > actor->x1AD8)
                result = actor->x1540 == 0;
        }
        return result;
    }
    case 1: case 2: case 3: case 18: case 20: case 21:
        break;
    }
    return 1;
}
