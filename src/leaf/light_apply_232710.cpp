// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00232710: sibling of func_001479A0. When the object's mask intersects the scene light mask, ask the scene for the lights
// that reach the object position (func_0018E500 returns four per-light weights in a vector); every light slot with a non-zero weight whose
// link is of kind 2 or 13 is drawn once through a scale matrix (distance attenuation clq/limit from the scene block at +0x4E00/+0x4E10)
// and its weight is cleared; if weights remain they are drawn together at the end.
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct MAT { float m[4][4]; } __attribute__((aligned(16)));
struct VTE { short d; short pad; void *pfn; };
struct CLQ { float g0, g1, g2, gUnused; };
struct LM { float gMin, gMax; };
struct LINK { char pad[8]; int kind; };
struct OBJ { char pad[0xC]; VTE *pvt; char pad10[0x300 - 0x10]; LINK *p300; };
struct ALO { char pad[0x40]; M4 m; };
struct P {
    char pad0[0xC]; VTE *pvt; char pad10[0x2C - 0x10]; unsigned char b2C; char pad2D[0x34 - 0x2D]; float g34;
    char pad38[0x50 - 0x38]; ALO *p50; char pad54[0x70 - 0x54]; char sub70[0x10]; qword v80; float g90;
    char pad94[0x104 - 0x94]; float g104; char pad108[0x10C - 0x108]; int x10C;
};
struct SW {
    char pad[0x3E04]; int grf3E04; char pad3E08[0x3EB8 - 0x3E08]; int c3EB8; OBJ *ap3EBC[5]; qword q3ED0;
    char pad3EE0[0x4E00 - 0x3EE0]; CLQ clq; LM lm;
};
extern "C" {
extern SW D_00475480;
void func_0023CBE0();
qword func_0011D5C8(M4 *pm, qword v);
qword func_0018E500(SW *psw, qword q, int k, qword v, float g);
void *memset(void *p, int c, unsigned int n) __asm__("func_00292034");
void func_0011D558(M4 *pm, M4 *pa, M4 *pb);
void func_0011D768(M4 *pm, M4 *pa);
qword func_001C8548(int i);
void func_0018E800(void *p, qword q, M4 *pm, int k, float a, float b);
void func_00232710(P *p);
}
union U { qword q; float f[4]; };
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("lw %0, %1" : "=rj"(q) : "m"(f)); } };
static inline M4 *Matrix(void *pv) { OBJ *p = (OBJ *)pv; VTE *e = &p->pvt[36]; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
static inline float GetX(qword v) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(v)); return f; }
static inline float GetY(qword v) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(v)); return f; }
static inline float GetZ(qword v) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(v)); return f; }
struct VU_VECTOR {
    qword q;
    VU_VECTOR(float x, float y, float z, float w)
    {
        qword t, s;
        __asm__("mfc1 %0,%3\n\tmfc1 %1,%4\n\tpextlw %0,%1,%0\n\tmfc1 %1,%5\n\tmfc1 %2,%6\n\tpextlw %1,%2,%1\n\tpcpyld %0,%1,%0"
                : "=&r"(q), "=&r"(t), "=&r"(s) : "f"(x), "f"(y), "f"(z), "f"(w));
    }
};
static inline float Distance(qword a, qword b)
{
    qword d, one; float f;
    register qword b2 __asm__("vf2") = b; /* register pin: b2 in vf2 */
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(d) : "j"(a), "j"(b2));
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(d));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(d) : "j"(d));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(d));
    return f;
}
static inline float GEvalClq(const CLQ *pclq, float g) { return pclq->g0 + g * (pclq->g1 + g * pclq->g2); }
static inline float GLimit(const LM *plm, float g)
{
    float lo = plm->gMin, hi = plm->gMax;
    if (g < lo) return lo;
    if (hi < g) return hi;
    return g;
}
static inline void Identity(MAT *pm)
{
    memset(pm, 0, sizeof(*pm));
    pm->m[3][3] = 1.0f;
    pm->m[2][2] = 1.0f;
    pm->m[1][1] = 1.0f;
}
static inline int FZero(qword v)
{
    int f;
    __asm__("vadd.xyzw $vf0, %1, %1\n\tvnop\n\tvnop\n\tvnop\n\tvnop\n\tcfc2.ni %0, $vi17" : "=r"(f) : "j"(v));
    return ((f & 0xF) ^ 0xF) == 0;
}
void func_00232710(P *p)
{
    if (!(p->b2C & D_00475480.grf3E04))
        return;
    func_0023CBE0();
    float w4 = GetX(VU_FLOAT(p->g90).q);
    qword v = VU_VECTOR(GetX(p->v80), GetY(p->v80), GetZ(p->v80), w4).q;
    qword t = func_0011D5C8(Matrix(p), v);
    U w;
    w.q = func_0018E500(&D_00475480, D_00475480.q3ED0, p->b2C, t, p->g34);
    for (int i = 0; i < D_00475480.c3EB8; i++) {
        if (w.f[i] == 0.0f)
            continue;
        OBJ *po = D_00475480.ap3EBC[i];
        if (po->p300 && (po->p300->kind == 2 || po->p300->kind == 13)) {
            w.f[i] = 0.0f;
            qword a = Matrix(p)->r[3];
            float g = GLimit(&D_00475480.lm, GEvalClq(&D_00475480.clq, Distance(a, Matrix(po)->r[3])));
            MAT ms;
            Identity(&ms);
            ms.m[0][0] = g;
            ms.m[1][1] = g;
            ms.m[2][2] = g;
            M4 mw = p->p50->m;
            M4 m3, m1, m2;
            M4 *pm3 = &m3;
            func_0011D558(&m1, &mw, (M4 *)&ms);
            func_0011D768(&m2, &mw);
            func_0011D558(pm3, &m1, &m2);
            func_0018E800(p->sub70, func_001C8548(i), pm3, p->x10C, p->g104, p->g104);
        }
    }
    if (!FZero(w.q))
        func_0018E800(p->sub70, w.q, 0, p->x10C, p->g104, p->g104);
}
