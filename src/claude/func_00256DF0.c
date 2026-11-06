// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Cf. Sly 2 src/hand/func_0020B210.c.
struct T { int x0; int x4; };
struct S { char pad[0x10F0]; int state; int arg; char pad2[0x1730 - 0x10F8]; struct T *p1730; };
void func_0024F3B8(struct S *p, int a, int b);
void func_002495E0(int a, int b);
void func_00256DF0(struct S *p)
{
    switch (p->state) {
    case 0:
        func_0024F3B8(p, p->arg, 0);
        break;
    case 1:
        func_0024F3B8(p, p->arg, 0);
        break;
    case 2:
        func_0024F3B8(p, p->arg, 0);
        func_002495E0(p->arg, 0);
        break;
    case 3:
        func_0024F3B8(p, p->p1730->x4, 0);
        p->p1730 = 0;
        break;
    }
    p->arg = 0;
    p->state = -1;
}
