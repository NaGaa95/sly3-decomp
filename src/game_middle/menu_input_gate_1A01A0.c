// SLY3_CFLAGS: -Os -G0
extern char D_003751D0[], D_0046FBE0[];
int func_0021DD30(void *menu);
unsigned int func_001A7980(int mask);
int func_001A01A0(void)
{
    if (func_0021DD30(D_003751D0) == 0 && func_0021DD30(D_0046FBE0) == 0 && func_001A7980(0xF0) != 0)
        return 1;
    return 0;
}
