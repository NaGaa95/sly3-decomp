// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct State { int unknown; float timestamp; int selector; } State;
extern int D_00349900[];
extern float D_0036BB98;
// Select only a registered event, recording its current clock value.
void func_002566F0(State *state, int selector)
{
    if (D_00349900[selector]) {
        float timestamp = D_0036BB98;
        state->selector = selector;
        state->timestamp = timestamp;
    }
}
