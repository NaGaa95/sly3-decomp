// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0016CB38: target-tracking state change (st 0 aims the actor at its target, -1 tears down).
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=rj"(q) : "f"(f)); } };
struct VU_FLOATQ { qword q; VU_FLOATQ(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
struct M4 { qword r[4]; };
struct BLOB { char b[16]; };
struct LO;
struct LOV { char pad[0x40]; short d40; short p40; void (*pfn40)(LO *); char pad48[0x120 - 0x48]; short d; short p; M4 *(*pfnMat)(LO *, ...); };
struct ASEG { char pad[0x58]; float g58; };
struct ENTRY { int k; ASEG *paseg; int pad[2]; };
struct LO { int a[3]; LOV *pvt; };
struct CTL { char pad[0x10DC]; struct CTL2 *p10DC; char pad10E0[0x1520 - 0x10E0]; int k1520; };
struct CTL2 { char pad[0x60]; float g60; float g64; };
struct ACT { LO lo; char pad10[0x1BC - 0x10]; float g1BC; char pad1C0[0x29C - 0x1C0]; char ab29C[0x2F4 - 0x29C]; BLOB b2F4; char pad304[0x364 - 0x304]; int f364; char pad368[0x1080 - 0x368]; int x1080; };
struct SO { LO lo; char pad10[0x40 - 0x10]; ENTRY *pentry; char pad44[0xCC - 0x44]; int xCC; char padD0[0xF0 - 0xD0]; float gF0; };
struct TGT { char pad[0x14]; LO *plo; char pad18[0x20 - 0x18]; unsigned int grf; char pad24[0x40 - 0x24]; qword v40; };
struct X { char pad[0x10]; ACT *pact; char pad14[0x18 - 0x14]; char ab18[0x30 - 0x18]; TGT *ptgt; float g34; float g38; ENTRY *aentry; int pad40; int st; float t48; };
extern "C" {
extern struct CLOCK { float t; float dt; } g_clock;
extern qword D_00317560;
extern char D_00475480[];
extern void *D_0038AE90;
extern char D_0036E740[];
void func_00238AE8(void *p);
void func_00238AB8(X *p);
int func_0013B500(LO *plo, int n);
qword func_001C94E8(LO *a, LO *b, qword v);
float atan2f(float y, float x);
void func_0024E878(ACT *p, float g);
void func_00256828(ACT *p, int a, int b, qword v);
void *func_001F4AD0(void *p, int n);
int func_001C8F20(LO *plo, void *pv);
void func_001A9058(void *p, int n, float g);
int func_00240DD8(unsigned int grf);
ENTRY *func_00255130(ACT *p, BLOB *pb);
SO *func_00238690(void *p, int n);
float func_0011E3B8(float g);
qword func_0011FD70(float a, float b, float c);
void func_00132930(SO *p, qword v);
void func_0016CB38(X *p, int st);
}
static inline M4 *VMat(LO *plo) { return plo->pvt->pfnMat((LO *)((char *)plo + plo->pvt->d)); }
static inline qword MulAdd(VU_VECTOR a, VU_VECTOR b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(r) : "j"(a.q), "j"(s.q), "0"(b.q));
    return r;
}
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Add(qword a, qword b) { qword d; __asm__("vadd.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Scale(qword a, VU_FLOATQ s) { qword d; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(d) : "j"(a), "j"(s.q)); return d; }
static inline qword Normalize(qword v)
{
    qword d, one, l, r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static inline float Length(qword v)
{
    qword d, one, l;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
    return g;
}

void func_0016CB38(X *p, int st)
{
    if (st == p->st)
        return;
    func_00238AE8(p->ab18);
    p->st = st;
    p->t48 = g_clock.t;
    if (st != -1) {
    if (st != 0)
        return;
    LO *plo = p->ptgt->plo;
    if (func_0013B500(plo, 0x32)) {
        VU_VECTOR pos = VMat(&p->pact->lo)->r[3];
        VU_VECTOR posTgt = VMat(plo)->r[3];
        VU_FLOAT s(-150.0f);
        VU_VECTOR dir = plo->pvt->pfnMat((LO *)((char *)plo + plo->pvt->d), s)->r[0];
        qword v = Sub(pos.q, MulAdd(posTgt, dir, s));
        if (func_0013B500(plo, 0x35) && ((CTL *)plo)->k1520 == 0xD) {
            U u;
            u.q = func_001C94E8(0, plo, v);
            u.f[0] *= 0.25f;
            v = func_001C94E8(plo, 0, u.q);
        }
        p->ptgt->v40 = Scale(Normalize(v), VU_FLOATQ(500.0f));
    }
    if (p->ptgt->grf != 0x40000 && p->ptgt->grf != 0x20000) {
        TGT *ptgt = p->ptgt;
        float g;
        if (1e-4f < Length(ptgt->v40)) {
            U *pu = (U *)&ptgt->v40;
            g = atan2f(-pu->f[1], -pu->f[0]);
        } else {
            M4 *pm = VMat(&p->pact->lo);
            g = atan2f(((U *)&pm->r[0])->f[1], ((U *)&pm->r[0])->f[0]);
        }
        func_0024E878(p->pact, g);
    }
    func_00256828(p->pact, 0, 0, D_00317560);
    p->g38 = 3.40282347e+38f;
    p->g34 = 3.40282347e+38f;
    p->pact->x1080 = 0;
    if (p->pact->f364) {
        void *pv = func_001F4AD0(D_00475480, 0);
        if (pv && func_001C8F20(p->ptgt->plo, pv) && (pv == D_0038AE90 || (p->ptgt->grf & 0x40000))) {
            func_001A9058(D_0036E740, 3, 0.15f);
            p->g34 = g_clock.t + 0.0500000045f;
        }
        p->g38 = g_clock.t + 0.13333334f;
    }
    ENTRY *pentry = &p->aentry[func_00240DD8(p->ptgt->grf)];
    if (pentry->k == -1) {
        BLOB b = p->pact->b2F4;
        pentry = func_00255130(p->pact, &b);
    }
    if (pentry->k == 2) {
        float gF0 = 1.0f;
        SO *pso = func_00238690(p->pact->ab29C, 0xCB);
        float gScale = gF0;
        pso->xCC = 0;
        if (func_0013B500(plo, 0x33)) {
            CTL2 *pc = ((CTL *)plo)->p10DC;
            if (pc) {
                gScale = pc->g60;
                gF0 = pc->g64;
            }
        }
        float gAng = func_0011E3B8(p->pact->g1BC + 3.14159274f);
        qword v = func_0011FD70(gAng, pentry->paseg->g58 * gScale, 0.0f);
        func_00132930(pso, Add(VMat(&p->pact->lo)->r[3], v));
        pso->gF0 = gF0;
        pso->pentry = pentry;
        pso->lo.pvt->pfn40((LO *)((char *)pso + pso->lo.pvt->d40));
    } else {
        SO *pso = func_00238690(p->pact->ab29C, 0xC9);
        pso->pentry = pentry;
        pso->lo.pvt->pfn40((LO *)((char *)pso + pso->lo.pvt->d40));
    }
    } else {
        func_00238AB8(p);
    }
}
