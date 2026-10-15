// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct WaitAction {
    char opaque00[0x30];
    void *target;
};
struct ActionWaitState {
    char opaque00[0x10];
    void *owner;
    int unused14;
    struct WaitAction *action;
    char opaque1C[0x30 - 0x1C];
    int mode;
    char opaque34[0x40 - 0x34];
    void *desired_target;
};
extern "C" {
void func_002389A0(void *);
int func_00254B80(void *);
void func_001A5138(void *);
void func_001A5038(void *, int);
int func_00238AD0(void *);
int func_00238AA8(void *);

void func_001A5510(void *receiver)
{
    struct ActionWaitState *state = (struct ActionWaitState *)receiver;
    int blocked, previous;
    func_002389A0(state);
    blocked = func_00254B80(state->owner);
    func_001A5138(state);
    while (!func_00238AA8(state)) {
        previous = state->mode;
        switch (previous) {
        case 0:
            if (blocked)
                func_001A5038(state, 2);
            else if (state->desired_target)
                func_001A5038(state, 1);
            break;
        case 1:
            if (blocked) {
                func_001A5038(state, 2);
            } else if (state->desired_target &&
                       state->desired_target != state->action->target) {
                func_001A5038(state, -1);
                func_001A5038(state, 1);
            } else if (!state->desired_target || func_00238AD0(state)) {
                func_001A5038(state, 0);
            }
            break;
        case 2:
            if (!blocked)
                func_001A5038(state, 0);
            break;
        }
        if (previous == state->mode)
            break;
    }
}
}
