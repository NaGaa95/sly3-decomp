// Return the original integer flag mask for the actual actor state.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions

struct ActorQueryState {
    char prefix[0x214];
    int disabled;
    char gap[0x19E0 - 0x218];
    int state;
};

int func_00156388(void *);

int func_001AFB70(struct ActorQueryState *receiver)
{
    if (receiver->disabled) {
        return 0;
    }
    switch (receiver->state) {
    case 4:
    case 9:
    case 17:
        return 0;
    case 19:
        return 15;
    default:
        return func_00156388(receiver);
    }
}
