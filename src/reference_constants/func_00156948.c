// SLY3_CFLAGS: -Os -G0
int func_0023E178(void *p, void *a);
int func_00272FB0(void *p, void *a, int b);
int func_00208A08(void *p, void *a, int b);
int func_00156948(char *p, void *a)
{
    int x = func_0023E178(p, a);
    x = func_00272FB0(p + 0x1290, a, x);
    return func_00208A08(p + 0x940, a, x);
}
