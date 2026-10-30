// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct E0C { int id; int a; int b; };
struct S00154798 { char pad[0x1250]; struct E0C e[3]; };
extern int D_00349040[];

int func_00154798(struct S00154798 *p, int id)
{
    int mask = 0;
    int i;
    for (i = 0; i < 3; i++) {
        if (id == p->e[i].id) {
            mask |= D_00349040[i];
        }
    }
    return mask;
}
