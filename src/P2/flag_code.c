// SLY3_CFLAGS: -Os -G0
struct FlagState { char unknown_0[0x3B8]; unsigned int flags; };
int func_002463A0(struct FlagState *state)
{
    return (state->flags & 4) ? 2 : 1;
}
