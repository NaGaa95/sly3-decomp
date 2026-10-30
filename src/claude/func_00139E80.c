// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* func_00139BB0's flags plus 1/2 for whether the midpoint of the two probe results is above/below y = 0 */
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct XF { char pad[0x30]; qword pos; };
struct O { char pad[0xC]; struct VTE *vt; };
struct T { char pad[0x70]; qword v70; };
struct P { char pad[0x1AA4]; struct O *p1AA4; char pad2[0x1AC8 - 0x1AA8]; struct T *p1AC8; };
int func_00139BB0(struct P *p);
qword func_001C9428(int n, struct P *p, qword v);
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ qword Qmtc2(float g)
{
    qword v;
    __asm__("qmtc2.ni %1, %0" : "=j"(v) : "r"(g));
    return v;
}
static __inline__ qword Avg(qword a, qword b, qword s)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %1, %3x\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s));
    return r;
}
int func_00139E80(struct P *p)
{
    int f = func_00139BB0(p);
    struct O *po = p->p1AA4;
    struct XF *pxf = ((struct XF *(*)(void *))po->vt[36].pfn)((char *)po + po->vt[36].d);
    qword a = func_001C9428(0, p, pxf->pos);
    qword b = func_001C9428(0, p, p->p1AC8->v70);
    union { qword q; float f[4]; } u;
    u.q = Qmtc2(0.5f);
    if (GetY(Avg(a, b, u.q)) < 0.0f)
        f |= 2;
    else
        f |= 1;
    return f;
}
