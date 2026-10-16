// SLY3_CFLAGS: -Os -G0
extern void *D_0036AEAC;
void func_001D2818(void *object);

void func_00175870(char *p, int flags)
{
    D_0036AEAC = *(void **)(p + 0x64);
    if (flags & 1)
        func_001D2818(p);
}
