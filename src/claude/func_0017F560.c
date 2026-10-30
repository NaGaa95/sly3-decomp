// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef union { struct { qword r[4]; } q; float af[4][4]; } M4;
typedef union { float af[4]; qword q; } QF;
typedef struct LO LO;
typedef struct { char pad[0x120]; short d; short p; M4 *(*pfnMat)(LO *); } LOV;
struct LO { int a[3]; LOV *pvt; };
static inline M4 *VMat(LO *plo) { return plo->pvt->pfnMat((LO *)((char *)plo + plo->pvt->d)); }
union GFLAGS {
    unsigned long value;
    struct { unsigned long low : 32; unsigned long b32 : 8; unsigned long b40 : 8; unsigned long b48 : 8; unsigned long bits : 8; } __attribute__((packed)) fields;
} __attribute__((packed, aligned(8)));
typedef struct { char pad[0x28]; union GFLAGS flags; char pad1[0x104 - 0x30]; float g104; } GEOM;
typedef struct { char pad[0x4AC]; void *p4AC; } SW;
typedef struct { LO lo; char pad[0x11B4 - 0x10]; SW *p11B4; } OW;
typedef struct {
    OW *p0; int pad4[4]; int k14; int pad18[8]; GEOM *p38; void *p3C; void *p40; LO *p44; int pad48[2];
    qword v50; qword v60; qword v70; qword v80; qword v90; QF vA0;
} X;
extern qword D_00479350;
qword func_001C9428(void *p, int n, qword q);
qword func_001C94E8(void *p, int n, qword q);
M3 *func_0011CBF0(M3 *pm, qword x, qword y);
qword *func_002BA818(qword *p, qword v);
void func_001C8248(void *p, qword q, M4 *pm, float g0, float g1);
void func_001C8328(void *p, qword q, qword a, qword b, float g0, float g1);
void func_0017F560(X *p);
static __inline__ qword VLen(qword c)
{
    qword l, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(l), "=&j"(one) : "j"(c));
    {
    qword r;
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(r) : "j"(l));
    return r;
    }
}
static __inline__ void VNormalize(qword *pr, qword c, qword k)
{
    qword l;
    register qword t __asm__("vf1"); /* register pin (the only one): result reg of the normalize */
    float gl;
    l = VLen(c);
    __asm__("qmfc2.ni %0, %1" : "=r"(gl) : "j"(l));
    if (gl < 1e-4f) {
        __asm__("" : "+r"(k));
        t = k;
    } else {
        __asm__ __volatile__("vdiv Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, Q" : "=j"(t) : "j"(c), "j"(l));
    }
    *pr = t;
}
static inline qword MulAffine(const M4 *pm, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(pm->q.r[0]), "j"(pm->q.r[1]), "j"(pm->q.r[2]), "j"(pm->q.r[3]), "j"(v));
    return r;
}
void func_0017F560(X *p)
{
    if (!p->p38 || !(p->p38->flags.fields.bits & 1))
        return;
    if (p->k14 == 2) {
        SW *psw = p->p0->p11B4;
        qword *pdir = &p->v90;
        QF *pv;
        p->v80 = func_001C9428(psw->p4AC, 0, p->v60);
        VNormalize(pdir, func_001C94E8(psw->p4AC, 0, p->v70), *pdir);
        pv = &p->vA0;
        pv->af[2] = 0.0f;
        pv->af[1] = 0.0f;
        p->vA0.af[0] = 0.0f;
    }
    {
    float g = p->p38->g104;
    M4 m4;
    M3 m3;
    M4 *pm4;
    func_0011CBF0(&m3, p->v90, VMat(&p->p0->lo)->q.r[0]);
    pm4 = &m4;
    func_002BA818(&pm4->q.r[3], p->v80);
    pm4->q.r[0] = m3.r[0];
    pm4->q.r[1] = m3.r[1];
    pm4->q.r[2] = m3.r[2];
    m4.af[2][3] = 0.0f;
    m4.af[1][3] = 0.0f;
    m4.af[0][3] = 0.0f;
    pm4->af[3][3] = 1.0f;
    if (p->p40)
        func_001C8248(p->p40, D_00479350, pm4, g, g);
    if (p->p3C && p->p44) {
        M4 *pm = VMat(p->p44);
        func_001C8328(p->p3C, D_00479350, pm->q.r[3], MulAffine(&m4, p->v50), g, g);
    }
    }
}
