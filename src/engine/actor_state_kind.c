// SLY3_CFLAGS: -Os -G0
struct ActorStateKindView { unsigned char prefix[0x1520]; int state; };
int func_0013F128(struct ActorStateKindView *receiver)
{
    switch(receiver->state) {
    case -1: return -1;
    case 0: return 0;
    case 2: return 1;
    case 3: return 2;
    case 4: return 3;
    case 11: return 4;
    case 12: return 5;
    case 13: return 6;
    case 14: return 7;
    case 17: return 9;
    case 5: case 6: case 7: return 10;
    }
    return 11;
}
