// SLY3_CFLAGS: -Os -G0
struct S0 { char pad[0x50]; int n; };
int func_0016E588(struct S0 *p)
{
    return p->n != 3 ? 1 : 7;
}
