// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Restructured from the matched Sly 2 source src/hand/func_0012D220.c for the Sly 3 version of the function.
// posT is a VU_VECTOR stack object (0x80), dv a spilled qword (0x70); the matrix call sits in both branches
// (cross-jumped at the jal) with the C++ return temporary at 0x30 shared by both; separate ag0/ag1 floats.
extern "C" {
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct VTE { short d; short pad; void *pfn; };
struct POLY { float a, b, c; };
struct O { int pad[6]; struct VTE *pvt; };
struct T { char pad[0x30]; qword pos; };
struct OB { int pad[3]; struct VTE *vt; };
struct X { char pad[0x70]; qword v70; char pad80[0x90 - 0x80]; struct P *p90; char pad94[0xA0 - 0x94]; int xA0; };
struct P {
    int x0; void *x4; struct X *x8; int xC; int pad10[4]; qword v20; struct POLY poly30; int pad3C; struct POLY poly40; int pad4C;
    float g50; float g54; float g58; float g5C; float g60; int x64; int x68; int x6C; struct OB *x70;
};
struct S3 { qword a, b, c; };
}
struct VU_VECTOR { qword q; VU_VECTOR() {} VU_VECTOR(const qword &v) { q = v; } };
extern "C" {
extern char D_00475480[];
struct OB *func_0017E1B8(void *pg, int k, int n, void *pv);
struct OB *func_001F4C40(void *pg, qword pos);
void func_0028EE98(void *a, struct X *b);
qword func_0028E990(int n, int k, qword v);
void func_00120528(qword q, float *pa, float *pb);
struct S3 func_0011C9E8(qword pos);
void func_0028C058(void *a, struct X *b, struct S3 *s);
static __inline__ float GEval(struct POLY *pp, float t) { return pp->a + t * (pp->b + t * pp->c); }
static __inline__ float GClamp(float g, float lo, float hi) { float r; if (g < lo) r = lo; else if (hi < g) r = hi; else r = g; return r; }
static __inline__ qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}

void func_0012F6B8(struct P *p)
{
    struct S3 s;
    qword dv;
    VU_VECTOR posT;
    struct OB *po;
    float g;
    int k;
    qword pos;

    if (p->x70 == 0 && p->x6C != -1)
        p->x70 = func_0017E1B8(D_00475480, 0x104, p->x6C, p->x4);
    posT = VU_VECTOR(p->x8->v70);
    po = p->x70;
    if (!po)
        po = func_001F4C40(D_00475480, posT.q);
    if (po) {
        qword d, t;
        struct T *pt = ((struct T *(*)(void *))po->vt[36].pfn)((char *)po + po->vt[36].d);
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pt->pos), "j"(posT.q));
        dv = d;
        qword x, l;
        __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(x), "=j"(t) : "j"(d), "j"(dv));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(x));
        __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
    } else {
        g = 3.402823466e+38f;
    }
    k = (p->g60 < g) ? p->x68 : p->x64;
    if (k != p->xC) {
        struct P *p90;
        p->xC = k;
        func_0028EE98(p->x4, p->x8);
        p90 = p->x8->p90;
        if (p90 != p) {
            struct O *po2 = (struct O *)p90;
            ((void (*)(struct O *))po2->pvt[4].pfn)((struct O *)((char *)po2 + po2->pvt[4].d));
            return;
        }
    }
    if (p->g60 < g) {
        s = func_0011C9E8(p->v20);
    } else {
        float ag0, ag1;
        func_00120528(func_0028E990(0, p->x8->xA0, dv), &ag0, &ag1);
        ag0 = GClamp(GEval(&p->poly30, ag0), p->g50, p->g54);
        ag1 = GClamp(GEval(&p->poly40, ag1), p->g58, p->g5C);
        {
            U u;
            u.q = Make(0.0f, -ag1, ag0);
            pos = u.q;
        }
        s = func_0011C9E8(pos);
    }
    func_0028C058(p->x4, p->x8, &s);
}
}
