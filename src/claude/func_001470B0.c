// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x314]; unsigned int c; int a[2]; };
void func_001470B0(struct S *s, int v)
{
    if (s->c < 2) {
        s->a[s->c++] = v;
    }
}
