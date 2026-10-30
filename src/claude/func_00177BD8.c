// SLY3_CFLAGS: -Os -G0
struct S0 { char pad[0xD0]; int n; };
struct S0 *func_00177BD8(struct S0 *p, int n)
{
    if (n == 1) p->n = n;
    return p;
}
