// Test whether an object is the player selected by `which` (0, 1 or any other value for either).
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
void *func_001F4AD0(void *game, int index);

int func_001F4350(void *object, int which)
{
    if (which != 1) {
        if (object == func_001F4AD0(D_00475480, 0))
            return 1;
    }
    if (which != 0) {
        if (object == func_001F4AD0(D_00475480, 1))
            return 1;
    }
    return 0;
}

int func_001F43C0(void)
{
    return 0;
}
