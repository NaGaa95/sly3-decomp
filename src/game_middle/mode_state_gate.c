// SLY3_CFLAGS: -Os -G0
struct ModeState {
    unsigned char prefix[0x16A8];
    int mode;
    unsigned char gap[0x16E4 - 0x16AC];
    int count;
};
int func_001F4618(char *);
int func_001EA940(struct ModeState *state)
{
    int result;
    switch (state->mode) {
    case 0:
    case 1:
        result = 0;
        if (state->count > 0)
            result = func_001F4618((char *)state) != 0;
        return result;
    case 2:
        return 1;
    default:
        return 0;
    }
}
