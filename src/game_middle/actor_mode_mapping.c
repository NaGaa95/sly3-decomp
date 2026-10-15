// SLY3_CFLAGS: -Os -G0
struct ActorModes {
    unsigned char opaque00[0x324];
    int action;
    unsigned char opaque328[0x1520 - 0x328];
    int state;
    unsigned char opaque1524[0x1540 - 0x1524];
    void *attachment;
};
void func_001DE690(void *actor, int state);
void func_001E04E8(void *actor);
void func_001E0770(struct ActorModes *actor, int mode)
{
    switch (mode) {
    case -1: func_001DE690(actor, -1); break;
    case 0:
        if (actor->attachment) func_001DE690(actor, 5);
        else func_001DE690(actor, 0);
        break;
    case 1:
        switch (actor->action) {
        case 14: case 15: break;
        default: func_001E04E8(actor); break;
        }
        func_001DE690(actor, 2);
        break;
    case 2: func_001DE690(actor, 14); break;
    case 3: func_001E04E8(actor); func_001DE690(actor, 15); break;
    case 4: func_001DE690(actor, 17); break;
    case 5: func_001E04E8(actor); func_001DE690(actor, 18); break;
    case 6: func_001E04E8(actor); func_001DE690(actor, 19); break;
    case 7: func_001E04E8(actor); func_001DE690(actor, 20); break;
    case 8: func_001E04E8(actor); func_001DE690(actor, 21); break;
    case 10: func_001E04E8(actor); func_001DE690(actor, 10); break;
    }
}
int func_001E08F8(struct ActorModes *actor)
{
    switch (actor->state) {
    case -1: return -1;
    case 0: case 5: return 0;
    case 2: return 1;
    case 14: return 2;
    case 15: return 3;
    case 17: return 4;
    case 18: return 5;
    case 19: return 6;
    case 20: return 7;
    case 21: return 8;
    case 10: return 10;
    }
    return 11;
}
