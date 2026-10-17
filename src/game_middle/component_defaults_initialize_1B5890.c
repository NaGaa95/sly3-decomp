// SLY3_CFLAGS: -Os -G0
struct ComponentState {
    int enabled00;
    unsigned char opaque04[8];
    int cleared0C;
    unsigned char opaque10[8];
    int enabled18;
    unsigned char opaque1C[8];
    int cleared24;
    unsigned char opaque28[0xD0];
    int cleared0F8;
    int cleared0FC;
    unsigned char opaque100[4];
    int cleared104;
    int cleared108;
    int value10C;
    void *handler110;
    unsigned char opaque114[0x7];
    int cleared11C;
    int cleared120;
    int value124;
    int cleared128;
    int value12C;
};
struct ComponentOwner { unsigned char opaque[0x68]; struct ComponentState *state; };
struct ComponentState *func_002746B0(struct ComponentState *state, int mode);
extern char D_00345710[];
void func_001B5890(void *receiver)
{
    struct ComponentOwner *owner = (struct ComponentOwner *)receiver;
    struct ComponentState *state = owner->state;
    struct ComponentState *current;
    state->value12C = 5;
    state->handler110 = D_00345710;
    state->value124 = 3;
    state->value10C = 1;
    state->cleared0FC = 0;
    state->cleared0F8 = 0;
    state->cleared104 = 0;
    state->cleared108 = 0;
    state->cleared11C = 0;
    state->cleared120 = 0;
    state->cleared128 = 0;
    current = func_002746B0(state, 1);
    current->enabled18 = 1;
    current->enabled00 = 1;
    current->cleared24 = 0;
    current->cleared0C = 0;
}
