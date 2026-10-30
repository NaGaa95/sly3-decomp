// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ENT { int n0; int n4; unsigned char pad[0x1C]; };
struct Self { unsigned char pad[0x40]; int c; struct ENT *a; };
void func_00198970(struct Self *p, int x)
{
    int i = p->c;
    if (i < 0x80) {
        struct ENT *e;
        p->c = i + 1;
        e = &p->a[i];
        e->n0 = 1;
        e->n4 = x;
    }
}
