// SLY3_CFLAGS: -Os -G0
void func_00155270(void *p, int a, void *b);
void func_001552D8(char *p, int a, void *b)
{
    func_00155270(p, a, b);
    *(int *)(p + 0x11D8) = 1;
}
