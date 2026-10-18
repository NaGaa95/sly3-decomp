// SLY3_CFLAGS: -Os -G0
struct State { char pad[0x4C]; int selection; };
struct Owner {
    char pad[0x3C];
    int flags;
    char pad40[0x16C - 0x40];
    struct State *state;
};
void *func_0022F450(struct Owner *, int);
void func_001C9118(struct Owner *, int);
static inline void SetFlags(struct Owner *owner, int bits)
{
    int tagged = owner->flags;
    if ((tagged ^ 1) & 1)
        *(int *)tagged |= bits;
    else
        owner->flags = tagged | bits;
}
static inline void ClearFlags(struct Owner *owner, int bits)
{
    int tagged = owner->flags;
    int clear = bits;
    if (bits & 4) {
        unsigned int current = ((tagged ^ 1) & 1) ? *(unsigned int *)tagged : tagged;
        if (current & 0x20)
            clear = bits & ~4;
    }
    if ((tagged ^ 1) & 1)
        *(int *)tagged &= ~clear;
    else
        owner->flags = tagged & ~clear;
}
void func_0022F668(struct Owner *owner, int selection)
{
    if (selection != -1) {
        func_0022F450(owner, 1);
        func_001C9118(owner, 0);
        ClearFlags(owner, 0x40);
        SetFlags(owner, 0xC);
    } else {
        int bits = 0xC;
        func_001C9118(owner, 0);
        SetFlags(owner, 0x40);
        ClearFlags(owner, bits);
    }
    if (owner->state)
        owner->state->selection = selection;
}
