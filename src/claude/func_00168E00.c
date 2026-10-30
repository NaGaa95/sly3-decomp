// SLY3_CFLAGS: -Os -G0
struct S0 { char pad[0x310]; unsigned int c; int a[4]; };
void func_00168E00(struct S0 *p, int x)
{
    if (x && p->c < 4) {
        p->a[p->c++] = x;
    }
}
