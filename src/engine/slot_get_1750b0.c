// SLY3_CFLAGS: -Os -G0
extern unsigned char D_00475480[];
int func_00175070(int value);
int func_00175098(int index);
void *func_001750B0(int input)
{
    int slot = func_00175098(func_00175070(input));
    char *base = (char *)D_00475480;
    void **table = (void **)(base + 0x3EBC);
    return table[slot];
}
