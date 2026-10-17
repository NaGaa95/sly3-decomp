// SLY3_CFLAGS: -Os -G0
struct State {
    unsigned char prefix[0x40C];
    int mode;
    unsigned char gap[0x4A4 - 0x410];
    int blocked;
};
int func_001F1A08(struct State *state)
{
    int mode = state->mode;
    if (mode >= -1) {
        if (mode <= 0)
            return 0;
    }
    return state->blocked == 0;
}
