// SLY3_CFLAGS: -Os -G0
struct OwnerResetView {
    char prefix[0xC0];
    int flags;
    char before_selection[0x39C - 0xC4];
    int selection;
    char before_state[0x3F0 - 0x3A0];
    int state;
    char before_enabled[0x3FC - 0x3F4];
    int enabled;
    void *target;
    int phase_bits;
    int full_gain;
    int transient40C;
    int transient410;
    int transient414;
    char before_options[0x458 - 0x418];
    int option458;
    int option45C;
};
int func_001F43F0(void *owner);
void func_001F43D0(char *owner, int value);
void func_00207880(void *owner);
void func_002075E8(void *owner, int mode);
void func_00203F38(struct OwnerResetView *owner)
{
    func_001F43D0((char *)owner, func_001F43F0(owner));
    owner->selection = 0;
    owner->flags = 0;
    owner->phase_bits = 0;
    owner->full_gain = 0;
    owner->transient40C = 0;
    owner->transient410 = 0;
    func_00207880(owner);
    owner->state = 0;
    owner->transient414 = 0;
    owner->option45C = 0;
    owner->enabled = 1;
    owner->option458 = 1;
    func_002075E8(owner, 0);
}
