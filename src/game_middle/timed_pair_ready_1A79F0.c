// SLY3_CFLAGS: -Os -G0
extern int D_0036F790;
extern int D_00370950;
extern float D_0036BB98;
int func_001A79F0(int mode)
{
    int ready = 1;
    if (mode != 1) {
        int first = 0;
        if (D_0036F790 == 1 && 5.0f <= D_0036BB98)
            first = 1;
        ready = first;
    }
    if (mode != 0) {
        mode = 0;
        if (ready && D_00370950 == 1 && 5.0f <= D_0036BB98)
            mode = 1;
        ready = mode;
    }
    return ready;
}
