// SLY3_CFLAGS: -Os -G0
extern unsigned char D_0036E740[];
int func_001A7A80(void *input, int mask, float threshold);
int func_001A7890(int mask)
{
    int index;
    for (index = 0; index < 2; index++) {
        if (func_001A7A80(D_0036E740 + index * 0x11C0, mask, 0.0f))
            return index;
    }
    return -1;
}
