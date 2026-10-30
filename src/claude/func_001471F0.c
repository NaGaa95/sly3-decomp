// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x340]; unsigned int c; int a[4]; };
void func_001471F0(struct S *s, int v)
{
    if (s->c < 4) {
        s->a[s->c++] = v;
    }
}
