// SLY3_ASFIX: engine-divfix1
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct Q { char pad[0x18]; int x18; };
struct VTE { short d; short pad; void (*pf)(void *, ...); };
struct S { int a[3]; struct VTE *vt; char pad[0x130 - 0x10]; int x130; char pad1[0x190 - 0x134]; int x190; char pad2[0x1B0 - 0x194]; struct Q *x1B0; int *x1B4; int x1B8; int pad3; qword q1C0; char pad4[0x2AC - 0x1D0]; void *x2AC; };
extern qword D_00317530, D_00317550, D_00317560;
extern char D_0036E740[];
qword func_0028E910(int a, int b, qword q);
void func_0023D938(struct S *p, qword q);
void func_0023D9D0(struct S *p, qword q);
void func_0023EBF8(struct S *p, int n);
void func_0023EC98(struct S *p, int n);
void func_001C7A00(void *a, struct S *p, int n);
M3 *func_0011CBF0(M3 *pm, qword x, qword y);
void func_00287000(struct S *p);
void func_00286360(struct S *p, int n);
void func_00286630(struct S *p, int n);
void func_001A9058(void *p, int n, float f);
void *func_001F4A80(void *p);
void func_00167D38(void *p, int n);
static inline qword Project(qword v, qword n)
{
    register qword d asm("vf1"); /* pin: projection temp in vf1 */
    qword one, r;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(v), "j"(n));
    __asm__("vmulx.xyzw %0, %1, %0x" : "+j"(d) : "j"(n));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(v), "j"(d));
    return r;
}
static inline float Len(qword v, qword *pl)
{
    qword d, one, l;
    float f;
    int t;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(f), "=&r"(t) : "j"(l));
    *pl = l;
    return f;
}
static inline qword DivQ(qword v, qword l)
{
    qword r;
    __asm__ __volatile__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static inline qword NormalizeSafe(float lf, qword l, qword v, qword def)
{
    if (lf < 0.0001f)
        return def;
    return DivQ(v, l);
}
void func_00287080(struct S *p, struct Q *pq, int *pn, qword q, qword up)
{
    int n;
    if (pq->x18 == 1) {
        pq = 0;
        pn = 0;
        n = 0;
    } else {
        n = *pn;
    }
    p->x1B0 = pq;
    p->x1B4 = pn;
    p->x1B8 = n;
    p->q1C0 = func_0028E910(0, n, q);
    p->vt[10].pf((char *)p + p->vt[10].d, pq, n, 0x13);
    func_0023D938(p, D_00317560);
    func_0023D9D0(p, D_00317560);
    func_0023EBF8(p, 1);
    func_0023EC98(p, 1);
    func_001C7A00(p->x2AC, p, 3);
    {
        M3 m;
        qword v, l, def;
        float lf;
        v = Project(up, D_00317550);
        __asm__("" : "=r"(def) : "0"(D_00317530)); /* zero-insn copy: def load issues before the 1e-4 constant */
        lf = Len(v, &l);
        func_0011CBF0(&m, NormalizeSafe(lf, l, v, def), D_00317550);
        p->vt[35].pf((char *)p + p->vt[35].d, &m);
    }
    func_00287000(p);
    switch (p->x190) {
    case 2:
        break;
    case -1:
        func_00286360(p, 0);
        break;
    case 1:
        func_00286630(p, 1);
        func_001A9058(D_0036E740 + p->x130 * 0x11C0, 3, 0.2f);
        func_00167D38(func_001F4A80(p), 0);
        break;
    }
}
