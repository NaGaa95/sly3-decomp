// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct State { unsigned char pad[0x20C]; int states[3]; } State;
// Require all three original states to be either 5 or 6.
int func_001CAFC8(const State *state)
{
    unsigned int index = 0;
    do {
        int value = state->states[index];
        if (value >= 7 || (index++, value < 5))
            return 0;
    } while (index < 3);
    return 1;
}
