// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ProgressRemainingView {
    int enabled;
    int maximum;
    int target;
    int remaining;
    char reserved10[0x50 - 0x10];
    int retries;
};
extern "C" {
void func_001A77A0(void);
void func_00196A10(void);
void func_001F9610(void *receiver);
}

extern "C" void func_001F9570(void *receiver, int remaining)
{
    ProgressRemainingView *progress = (ProgressRemainingView *)receiver;
    func_001A77A0();
    if (progress->enabled) {
        if (progress->target == 0) {
            progress->target = remaining;
            progress->maximum = (int)((unsigned int)remaining * 2U);
            func_00196A10();
        } else if (progress->remaining == remaining) {
            progress->retries = (int)((unsigned int)progress->retries + 1U);
        } else {
            progress->retries = 0;
        }
        progress->remaining = remaining;
        func_001F9610(receiver);
    }
}
