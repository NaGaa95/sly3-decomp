// SLY3_CFLAGS: -Os -G0
struct TaperState { char prefix[0x30]; int mode; };
float func_00134B48(struct TaperState *state,float fraction)
{
    if(state->mode == 1) return 150.0f;
    if(state->mode != 2) return 0.0f;
    return (1.0f-fraction)*150.0f;
}
