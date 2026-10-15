// Reference algorithm: src/hand/func_00154E10.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct T {
    int pad[4];
    int x10, x14, x18, x1C;
    int pad20[2];
    int x28, x2C, x30, x34, x38, x3C, x40, x44;
} T;
typedef struct S { int x0; int x4; int pad[3]; T *p14; } S;
extern char D_0036BD20[];
extern char D_00475480[];
extern float func_00171C98(void *p);
extern int func_0011E8F0(int a, int b);
extern int func_0013B500(void *p, int k);
extern void func_001F85F8(void *p, int k, qword q, void *pv, int n);
static inline int NLerp(float g, int a, int b)
{
    if (a == b)
        return b;
    if (a < b)
        return a + (int)(g * ((float)b + 0.999f - (float)a));
    return b + (int)((1.0f - g) * ((float)a + 0.999f - (float)b));
}
void func_00171E50(S *p, qword q, int n, int dn, void *pv)
{
    if (p->x0 <= 0) {
        int a = NLerp(func_00171C98(D_0036BD20), p->p14->x28, p->p14->x30);
        int b = NLerp(func_00171C98(D_0036BD20), p->p14->x2C, p->p14->x34);
        p->x0 = func_0011E8F0(a, b);
    }
    if (p->x4 <= 0) {
        int a = NLerp(func_00171C98(D_0036BD20), p->p14->x38, p->p14->x40);
        int b = NLerp(func_00171C98(D_0036BD20), p->p14->x3C, p->p14->x44);
        p->x4 = func_0011E8F0(a, b);
    }
    {
        int d = func_0013B500(pv, 0x3A) ? -2 : -1;
        p->x0 += d;
        p->x4 += dn;
    }
    if (n < 0) {
        if (p->x0 <= 0)
            n = func_0011E8F0(p->p14->x10, p->p14->x14);
        else
            n = func_0011E8F0(p->p14->x18, p->p14->x1C);
    }
    if (n > 0)
        func_001F85F8(D_00475480, 0x67, q, pv, n);
    if (p->x4 <= 0)
        func_001F85F8(D_00475480, 0x69, q, pv, 1);
}
