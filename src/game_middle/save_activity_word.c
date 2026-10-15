// SLY3_CFLAGS: -Os -G0
struct SaveActivityView {
    unsigned char opaque00[0x1395C];
    int activity;
};

void func_001CFDE8(void *save, int activity)
{
    ((struct SaveActivityView *)save)->activity = activity;
}

int func_001CFDF8(void *save)
{
    return ((struct SaveActivityView *)save)->activity;
}
