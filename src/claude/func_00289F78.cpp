// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
union M4 { qword r[4]; float m[4][4]; };
struct VTE { short d; short pad; void *pfn; };
struct LO { char pad[0xC]; VTE *pvt; };
struct JT {
    int k; int imat; int irow; int pad0C; float g10; int pad14[3];
    union { qword q; float f[4]; } v20; union { qword q; float f[4]; } v30; qword q40; qword q50; qword q60;
    float g70, g74, g78; int pad7C;
};
struct S {
    char pad[0x40]; float t40; int cjt; int cmat; int n4C; char pad50[0x60 - 0x50]; JT ajt[8]; char pad460[0x10];
    M4 amA[4]; M4 amB[4]; M4 *pmA; M4 *pmB; char pad678[0x688 - 0x678]; LO *plo688;
};
struct P2 { char pad[0x9C]; int n9C; };
struct CLOCK { float t; float dt; };
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
extern CLOCK g_clock;
extern "C" {
void func_002897B8(S *, P2 *);
float func_0011E3B8(float);
void func_0011EB28(float, float *, float *);
void *memset(void *, int, unsigned int);
void func_0011D558(M4 *, const M4 *, const M4 *); // void return: a call_value changes the sched2 tie in the product loops
void func_00289F78(S *p, P2 *p2);
}
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); }
    // c is built per call from memory (lw via reload); the last-constructed temp of each call keeps its home store
    VU_FLOAT(float f, int, int) { __asm__("qmtc2.ni %1, %0" : "=j,!r"(q) : "r,m"(f)); }
};
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword VecCombo(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q));
    return r;
}
static inline qword VCA(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q), "j"(f1.q), "j"(f1.q), "j"(f2.q));
    return r;
}
static inline M4 *Matrix(LO *p) { VTE *e = &p->pvt[36]; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline void SetIdentity(M4 *pm)
{
    memset(pm, 0, sizeof(M4));
    pm->m[3][3] = 1.0f;
    pm->m[2][2] = 1.0f;
    pm->m[1][1] = 1.0f;
    pm->m[0][0] = 1.0f;
}
static inline M4 operator*(const M4 &a, const M4 &b) return r { func_0011D558(&r, &a, &b); }

void func_00289F78(S *p, P2 *p2)
{
    if (p2 && p2->n9C != p->n4C)
        func_002897B8(p, p2);
    if (g_clock.t == p->t40)
        return;
    for (int i = 0; i < p->cjt; i++) {
        JT *pjt = &p->ajt[i];
        M4 *pmA = &p->amA[pjt->imat];
        M4 *pmB = &p->amB[pjt->imat];
        switch (pjt->k) {
        case -1:
            break;
        case 0: {
            float s, c;
            func_0011EB28(func_0011E3B8((g_clock.t * pjt->g74 + pjt->g78) * 6.2831855f), &s, &c);
            VECTOR4 a, b;
            int row = pjt->irow;
            VECTOR4 *pa0 = (VECTOR4 *)pmA->m[row];
            int row1 = row + 1;
            VECTOR4 *pa1 = (VECTOR4 *)pmA->m[row1];
            VECTOR4 *pb0 = (VECTOR4 *)pmB->m[row];
            VECTOR4 *pb1 = (VECTOR4 *)pmB->m[row1];
            
            *(qword *)&a = VCA(VU_FLOAT(c, 0, 0), pjt->v30.q, VU_FLOAT(s), pjt->q50);
            pa0->x = pjt->g10 * a.x;
            pa0->y = pjt->g10 * a.y;
            pa0->z = pjt->g10 * a.z;
            *(qword *)&a = VecCombo(VU_FLOAT(-s), pjt->v30.q, VU_FLOAT(c, 0, 0), pjt->q50);
            pa1->x = pjt->g10 * a.x;
            pa1->y = pjt->g10 * a.y;
            pa1->z = pjt->g10 * a.z;
            *(qword *)&b = VecCombo(VU_FLOAT(c, 0, 0), pjt->q40, VU_FLOAT(s), pjt->q60);
            pb0->x = pjt->g10 * b.x;
            pb0->y = pjt->g10 * b.y;
            *(qword *)&b = VecCombo(VU_FLOAT(-s), pjt->q40, VU_FLOAT(c, 0, 0), pjt->q60);
            pb1->x = pjt->g10 * b.x;
            pb1->y = pjt->g10 * b.y;
            break;
        }
        case 1: {
            VECTOR4 *pa0 = (VECTOR4 *)pmA->m[pjt->irow];
            VECTOR4 *pb0 = (VECTOR4 *)pmB->m[pjt->irow];
            pa0->x = pjt->g10 * pjt->v20.f[0];
            pa0->y = pjt->g10 * pjt->v20.f[1];
            pa0->z = pjt->g10 * pjt->v20.f[2];
            pb0->x = pjt->g10 * pjt->v30.f[0];
            pb0->y = pjt->g10 * pjt->v30.f[1];
            break;
        }
        }
    }
    if (p->plo688) {
        M4 am[4];
        for (int k = 0; k < p->cmat; k++)
            SetIdentity(&am[k]);
        qword pos = Matrix(p->plo688)->r[3];
        for (int i = 0; i < p->cjt; i++) {
            JT *pjt = &p->ajt[i];
            if (pjt->k == 0) {
                float s, c;
                float ang = Dot(pos, pjt->v20.q) * 6.2831855f;
                func_0011EB28(pjt->g70 * ang, &s, &c);
                M4 *pm = &am[pjt->imat];
                int row = pjt->irow;
                pm->m[row][row] = c;
                pm->m[row + 1][row] = -s;
                pm->m[row][row + 1] = s;
                pm->m[row + 1][row + 1] = c;
            }
        }
        for (int k = 0; k < p->cmat; k++)
            p->pmA[k] = p->amA[k] * *(M4 *)((int)am + (k << 6));
        for (int k = 0; k < p->cmat; k++)
            p->pmB[k] = p->amB[k] * *(M4 *)((int)am + (k << 6));
    }
    p->t40 = g_clock.t;
}
