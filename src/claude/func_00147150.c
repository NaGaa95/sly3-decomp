// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x32C]; unsigned int c; int a[4]; };
void func_00147150(struct S *s, int v)
{
    if (s->c < 4) {
        s->a[s->c++] = v;
    }
}
