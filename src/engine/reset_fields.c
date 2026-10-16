// SLY3_CFLAGS: -Os -G0
struct EngineResetState {
    unsigned char p0[0x4C]; int f4C,f50,f54,f58;
    unsigned char p1[0x2C]; int f88,f8C,f90,f94,f98,f9C;
    unsigned char p2[8]; int fA8;
};
void func_00135F80(struct EngineResetState *state)
{
    state->fA8=0; state->f4C=0; state->f50=0; state->f54=0; state->f58=0;
    state->f88=0; state->f8C=0; state->f90=0; state->f94=0; state->f98=0; state->f9C=0;
}
