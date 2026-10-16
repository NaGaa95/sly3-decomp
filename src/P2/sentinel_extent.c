// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct SentinelExtentView {
    char prefix[0x1A8];
    float extent;
};

void func_001C7DC8(void *receiver);
float func_0022F998(void *receiver);

void func_001F31B0(void *receiver) {
    struct SentinelExtentView *p = (struct SentinelExtentView *)receiver;
    int unresolved;

    func_001C7DC8(receiver);
    unresolved = 1;
    if (p->extent != 1250.0f)
        unresolved = 0;
    if (unresolved != 0)
        p->extent = func_0022F998(receiver) + 1250.0f;
}
