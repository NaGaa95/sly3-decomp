// SLY3_ASFIX: engine-divfix1
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 port of the matched Sly 2 func_0011F960 `*` script builtin: tags 2 lower, short-tag CRef, float case split per pr tag, vector scale through a by-value VUF temp, matrix scale reads the VU float per element.
typedef int qword __attribute__((mode(TI)));
struct VECTOR { float x, y, z, w; };
struct MATRIX4 { float af[16]; } __attribute__((aligned(16)));
struct V8 { float x, y; };
struct VU_FLOATR {
    qword q;
    VU_FLOATR(const float &f) { __asm__("lw %0, %1" : "=r"(q) : "m"(f)); }
    float F() const { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
};
struct VU_FLOAT_M {
    qword q;
    VU_FLOAT_M(float f) { __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); }
    float F() const { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
};
struct VU_FLOAT_V {
    qword q;
    VU_FLOAT_V(const float &f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(const int *)&f)); }
};
struct VU_FLOAT_I {
    qword q;
    VU_FLOAT_I(int n) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(n)); }
};
struct VU_FLOAT_D { qword q; };
struct VU_FLOAT_F {
    qword q;
    VU_FLOAT_F(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); }
};
struct VU_FLOAT_X { qword q; VU_FLOAT_X(float f) __asm__("__8VU_FLOATf"); };
struct VU_VECTOR { qword q; VU_VECTOR(const VECTOR &v) __asm__("func_002BA808"); };
qword operator*(VU_FLOAT_X f, VU_VECTOR v) __asm__("__ml__FG8VU_FLOATG9VU_VECTOR");
extern "C" qword *func_002BA818(VECTOR *p, qword v);
extern "C" MATRIX4 func_0011D558(const MATRIX4 &a, const MATRIX4 &b);
struct CRef {
    short m_tagk; short m_cref; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(int n);
    CRef &operator=(float g);
    CRef &operator=(qword v) __asm__("func_0012B470");
    CRef &operator=(const MATRIX4 &m) __asm__("func_0012B4D8");
};
struct NODE { CRef ref; int x8; NODE *pnext; };
extern "C" CRef func_0012B928(CRef *pref, void *a, void *b);
extern "C" CRef func_001215D0(void *pv, CRef *aref);

static inline qword MulVF(const qword *pv, float g)
{
    VU_FLOAT_F s(g);
    qword r;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(s.q), "j"(*pv));
    return r;
}
static inline qword MulVFR(const CRef *pr, float g)
{
    VU_FLOAT_F s(g);
    qword r;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(s.q), "j"(*(const qword *)pr->u.pv));
    return r;
}
struct VUF {
    qword q;
    VUF(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); }
    VUF(const float &f, int) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(const int *)&f)); }
};
static inline void MulVec(qword *pq, VUF s)
{
    qword a = *pq, r;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(s.q), "j"(a));
    *pq = r;
}
static inline void ScaleInto(MATRIX4 *pmDst, const MATRIX4 *pm, VU_FLOAT_M s)
{
    for (int i = 0; i < 16; i++)
        pmDst->af[i] = s.F() * pm->af[i];
}
static inline void MulMatrixM(MATRIX4 *pm, float d)
{
    MATRIX4 mat;
    VU_FLOAT_M s(d);
    for (int i = 0; i < 16; i++)
        mat.af[i] = s.F() * pm->af[i];
    *pm = mat;
}
static inline void MulMatrix(MATRIX4 *pm, const float &d)
{
    MATRIX4 mat;
    VU_FLOATR s(d);
    for (int i = 0; i < 16; i++)
        mat.af[i] = s.F() * pm->af[i];
    *pm = mat;
}
static inline qword MulMatVec(const MATRIX4 *pm, const qword *pv)
{
    const qword *aq = (const qword *)pm;
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(aq[0]), "j"(aq[1]), "j"(aq[2]), "j"(aq[3]), "j"(*pv));
    return r;
}

static inline void Mul2(V8 *p, float d)
{
    p->x *= d;
    p->y *= d;
}
CRef func_001215D0(void *pv, CRef *aref)
{
    CRef ref;
    int fInt = 0;
    switch (aref[0].m_tagk) {
    case 0x13:
        ref = (float)aref[0].u.n;
        fInt = 1;
        break;
    case 0x14:
    case 0x18:
    case 0x19:
    case 0x1A:
    case 0x1B:
        ref = func_0012B928(&aref[0], 0, 0);
        break;
    }
    NODE *pn = 0;
    int bits;
    if (aref[1].m_tagk)
        pn = (NODE *)aref[1].u.pv;
    for (; pn; pn = pn->pnext) {
        CRef *pr = &pn->ref;
        switch (ref.m_tagk) {
        case 0x14:
            switch (pr->m_tagk) {
            case 0x14:
                fInt = 0;
                ref.u.g *= pr->u.g;
                break;
            case 0x13:
                ref.u.g *= (float)pr->u.n;
                break;
            case 0x18:
                ref = MulVFR(pr, ref.u.g);
                break;
            case 0x19: {
                MATRIX4 *pm = (MATRIX4 *)pr->u.pv;
                MATRIX4 mat;
                ScaleInto(&mat, pm, VU_FLOAT_M(ref.u.g));
                ref = mat;
                break;
            }
            case 0x1A: {
                float g = ref.u.g;
                ref.Decref();
                ref.InitTag(0x1A);
                VECTOR *pvec = (VECTOR *)ref.u.pv;
                VECTOR *pvSrc = (VECTOR *)pr->u.pv;
                func_002BA818(pvec, VU_FLOAT_X(g) * VU_VECTOR(*pvSrc));
                break;
            }
            case 0x1B: {
                float g = ref.u.g;
                ref.Decref();
                ref.InitTag(0x1B);
                V8 *ps = (V8 *)pr->u.pv;
                V8 *pd = (V8 *)ref.u.pv;
                pd->x = ps->x * g;
                pd->y = ps->y * g;
                break;
            }
            }
            break;
        case 0x18:
            switch (pr->m_tagk) {
            case 0x13: MulVec((qword *)ref.u.pv, VUF((float)pr->u.n)); break;
            case 0x14: MulVec((qword *)ref.u.pv, VUF(pr->u.g, 0)); break;
            }
            break;
        case 0x19:
            switch (pr->m_tagk) {
            case 0x13: MulMatrixM((MATRIX4 *)ref.u.pv, (float)pr->u.n); break;
            case 0x14: MulMatrix((MATRIX4 *)ref.u.pv, pr->u.g); break;
            case 0x18: ref = MulMatVec((MATRIX4 *)ref.u.pv, (qword *)pr->u.pv); break;
            case 0x19: {
                MATRIX4 *pm = (MATRIX4 *)ref.u.pv;
                *pm = func_0011D558(*pm, *(MATRIX4 *)pr->u.pv);
                break;
            }
            }
            break;
        case 0x1A:
            switch (pr->m_tagk) {
            case 0x13: {
                VECTOR *pvec = (VECTOR *)ref.u.pv;
                func_002BA818(pvec, VU_FLOAT_X((float)pr->u.n) * VU_VECTOR(*pvec));
                break;
            }
            case 0x14: {
                VECTOR *pvec = (VECTOR *)ref.u.pv;
                func_002BA818(pvec, VU_FLOAT_X(pr->u.g) * VU_VECTOR(*pvec));
                break;
            }
            }
            break;
        case 0x1B:
            switch (pr->m_tagk) {
            case 0x13: Mul2((V8 *)ref.u.pv, (float)pr->u.n); break;
            case 0x14: Mul2((V8 *)ref.u.pv, pr->u.g); break;
            }
            break;
        }
    }
    if (fInt && ref.m_tagk == 0x14)
        ref = (int)ref.u.g;
    return ref;
}
