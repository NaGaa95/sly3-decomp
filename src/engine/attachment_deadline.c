// SLY3_CFLAGS: -Os -G0
struct DeadlineStatePrefix {
    unsigned char opaque00[0x58];
    float deadline;
};
struct DeadlineClockPrefix { float time; };
extern struct DeadlineClockPrefix D_0036BB98;
void func_0016D480(void *receiver, int mode);
int func_00131850(void *receiver, int message, void *arguments);

static inline float HardwareMaximum(float first, float second)
{
    __asm__("max.s %0,%0,%1" : "+f"(first) : "f"(second));
    return first;
}

int func_0016D5D0(void *receiver, int message, void *arguments)
{
    struct DeadlineStatePrefix *state = receiver;
    if (message == 13) {
        func_0016D480(state, 0);
        state->deadline = HardwareMaximum(D_0036BB98.time + 5.0f, state->deadline);
        return 1;
    }
    return func_00131850(state, message, arguments);
}
