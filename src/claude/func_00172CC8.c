// SLY3_CFLAGS: -Os -G0
struct S1 { char pad[0xE0]; int n; };
struct S0 { char pad[0x58]; struct S1 *p; };
int func_00172CC8(struct S0 *p)
{
    int n = -1;
    if (p->p) n = p->p->n;
    return n;
}
