// SLY3_CFLAGS: -Os -G0
struct TimedActivationOwner {
    char prefix[0x324];
    void *primary;
    void *fallback;
    char gap32C[0x1144 - 0x32C];
    unsigned int flags;
};

struct TimedActivationState {
    char prefix[0x10];
    struct TimedActivationOwner *owner;
    char gap14[0x40 - 0x14];
    void *program;
};

void func_00238978(void);
int func_00254B80(void *);
void func_001EFAB8(void *, int);

void func_001EF880(void *receiver)
{
    struct TimedActivationState *state = (struct TimedActivationState *)receiver;
    struct TimedActivationOwner *owner;
    func_00238978();
    owner = state->owner;
    if (owner->primary) {
        state->program = owner->primary;
    } else if (owner->flags & 2) {
        state->program = owner->fallback;
    } else {
        state->program = 0;
        func_001EFAB8(state, 2);
        return;
    }
    if (func_00254B80(state->owner))
        func_001EFAB8(state, 3);
    else
        func_001EFAB8(state, 0);
}
