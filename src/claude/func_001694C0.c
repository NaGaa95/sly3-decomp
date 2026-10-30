// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S { char pad[0xD8]; int nD8; };
struct S *func_001694C0(struct S *p, int n)
{
    if (n == 1)
        p->nD8 = n;
    return p;
}
