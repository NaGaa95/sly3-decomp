// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S { char pad[0x1A4]; unsigned int c; int a[6]; };
void func_00171718(struct S *p, int x)
{
    unsigned int c = p->c;
    if (c < 6) {
        p->a[c] = x;
        p->c = c + 1;
    }
}
