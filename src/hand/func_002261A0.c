// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original Sly 3 state and record semantics.
typedef struct State { unsigned char pad[0x64]; int count; int values[16]; } State;
void func_002261A0(State *state, int value)
{
    int count = state->count;
    int index;
    for (index = 0; index < count; index++)
        if (state->values[index] == value)
            return;
    if ((unsigned int)count < 16) {
        state->values[count] = value;
        state->count = count + 1;
    }
}
