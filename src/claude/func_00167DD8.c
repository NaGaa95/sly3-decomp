// SLY3_CFLAGS: -Os -G0
void CopyAb(void *, void *, int);
void **func_00167DA8(void);
void func_00167DD8(void)
{
    void **base = func_00167DA8();
    void **p = base;
    int i;
    for (i = 2; i >= 0; i--) {
        char *q = *p++;
        if (q != 0) {
            CopyAb(q + 4, base + 4, 0x40);
        }
    }
}
