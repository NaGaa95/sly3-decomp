// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Is anything (other than self) within r of pos that blocks? (stack-allocated CTX scope)
typedef int qword __attribute__((mode(TI)));
struct CTX { int a[4]; CTX(); ~CTX(); };
struct SO { int x0; SO *p4; char pad[0x18 - 8]; unsigned long ul18; char pad20[0x84 - 0x20]; void *p84; };
struct G;
extern G D_00475480;
extern "C" {
int func_0025CE90(void *, SO *);
void func_0025D0D8(G *p, qword pos, float r, int (*pfn)(void *, SO *), void *ctx, int *pc, SO ***pap);
int func_001CD098(qword pos, SO *o, float r, int, int, int, int, void *);
int func_0026D228(qword pos, float r, SO *self);
}
int func_0026D228(qword pos, float r, SO *self)
{
    CTX ctx;
    char buf[0x30];
    int c;
    SO **a;
    int i;
    func_0025D0D8(&D_00475480, pos, r, func_0025CE90, 0, &c, &a);
    for (i = 0; i < c; i++) {
        SO *o = a[i];
        if (o->p4 == self)
            continue;
        if (o->ul18 & 0x20000)
            return 1;
        if (!o->p84)
            continue;
        if (func_001CD098(pos, o, r, 0x7FFFFFFF, 0, 0, 1, buf) > 0)
            return 1;
    }
    return 0;
}
