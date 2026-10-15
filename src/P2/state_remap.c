// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Partial receiver view; the transition helper owns the state changes. */
struct StateReceiver {
    char prefix[0x1470];
    int state;
};

void func_001F08B8(void *receiver, int state);

void func_001F0CE0(void *receiver, int state)
{
    switch (state) {
    case -1: func_001F08B8(receiver, -1); break;
    case 0: func_001F08B8(receiver, 0); break;
    case 1: func_001F08B8(receiver, 5); break;
    case 2: func_001F08B8(receiver, 6); break;
    case 3: func_001F08B8(receiver, 7); break;
    case 9: func_001F08B8(receiver, 8); break;
    case 10: func_001F08B8(receiver, 3); break;
    case 5: func_001F08B8(receiver, 9); break;
    case 6: func_001F08B8(receiver, 10); break;
    }
}

int func_001F0DA8(struct StateReceiver *receiver)
{
    switch (receiver->state) {
    case -1: return -1;
    case 0: return 0;
    case 5: return 1;
    case 6: return 2;
    case 7: return 3;
    case 8: return 9;
    case 3:
    case 4: return 10;
    case 9: return 5;
    case 10: return 6;
    default: return 11;
    }
}
