// SLY3_CFLAGS: -Os -G0
struct PendingState { char unknown_0[0x214]; int pending; };
unsigned int func_0024E2A8(struct PendingState *state)
{
    return state->pending ? 0 : 7;
}
