// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_ASFIX: engine-divfix1
// Sly 3 port (A16) of the matched Sly 2 func_0011FEC8 `/` builtin: tags 2 lower, short-tag CRef, float case split per pr tag, matrix scale reads the VU_FLOAT temp per element.
typedef int qword __attribute__((mode(TI)));
struct VECTOR { float x, y, z, w; };
struct MATRIX4 { float af[16]; } __attribute__((aligned(16)));
struct V8 { float x, y; };
struct VU_FLOATI {
    qword q;
    VU_FLOATI(float f) { __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); }
    float F() const { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
};
struct VU_FLOAT_X { qword q; VU_FLOAT_X(float f) __asm__("__8VU_FLOATf"); };
struct VU_VECTOR { qword q; VU_VECTOR(const VECTOR &v) __asm__("func_002BA808"); };
qword operator*(VU_FLOAT_X f, VU_VECTOR v) __asm__("__ml__FG8VU_FLOATG9VU_VECTOR");
extern "C" qword *func_002BA818(VECTOR *p, qword v);
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
};
struct NODE { CRef ref; int x8; NODE *pnext; };
extern "C" CRef func_0012B928(CRef *pref, void *a, void *b);
extern "C" CRef func_00121B28(void *pv, CRef *aref);

struct VU_FLOAT_V {
    qword q;
    VU_FLOAT_V(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); }
};
static inline void DivVector(qword *pq, float d)
{
    VU_FLOAT_V s(1.0f / d);
    qword a = *pq, r;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(s.q), "j"(a));
    *pq = r;
}

static inline void ScaleM(MATRIX4 *pm, VU_FLOATI s)
{
    MATRIX4 mat;
    for (int i = 0; i < 16; i++)
        mat.af[i] = s.F() * pm->af[i];
    *pm = mat;
}
static inline void DivMatrix(MATRIX4 *pm, float d)
{
    MATRIX4 mat;
    VU_FLOATI s(1.0f / d);
    for (int i = 0; i < 16; i++)
        mat.af[i] = s.F() * pm->af[i];
    *pm = mat;
}

CRef func_00121B28(void *pv, CRef *aref)
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
    if (aref[1].m_tagk)
        pn = (NODE *)aref[1].u.pv;
    for (; pn; pn = pn->pnext) {
        CRef *pr = &pn->ref;
        switch (ref.m_tagk) {
        case 0x14:
            switch (pr->m_tagk) {
            case 0x14:
                fInt = 0;
                ref.u.g /= pr->u.g;
                break;
            case 0x13:
                ref.u.g /= (float)pr->u.n;
                break;
            }
            break;
        case 0x18:
            switch (pr->m_tagk) {
            case 0x13: DivVector((qword *)ref.u.pv, (float)pr->u.n); break;
            case 0x14: DivVector((qword *)ref.u.pv, pr->u.g); break;
            }
            break;
        case 0x19:
            switch (pr->m_tagk) {
            case 0x13: ScaleM((MATRIX4 *)ref.u.pv, VU_FLOATI(1.0f / (float)pr->u.n)); break;
            case 0x14: DivMatrix((MATRIX4 *)ref.u.pv, pr->u.g); break;
            }
            break;
        case 0x1A:
            switch (pr->m_tagk) {
            case 0x13: {
                VECTOR *pvec = (VECTOR *)ref.u.pv;
                func_002BA818(pvec, VU_FLOAT_X(1.0f / (float)pr->u.n) * VU_VECTOR(*pvec));
                break;
            }
            case 0x14: {
                VECTOR *pvec = (VECTOR *)ref.u.pv;
                func_002BA818(pvec, VU_FLOAT_X(1.0f / pr->u.g) * VU_VECTOR(*pvec));
                break;
            }
            }
            break;
        case 0x1B: {
            float d;
            switch (pr->m_tagk) {
            case 0x13: d = (float)pr->u.n; break;
            case 0x14: d = pr->u.g; break;
            default: continue;
            }
            float s = 1.0f / d;
            V8 *p = (V8 *)ref.u.pv;
            p->x *= s;
            p->y *= s;
            break;
        }
        }
    }
    if (fInt && ref.m_tagk == 0x14)
        ref = (int)ref.u.g;
    return ref;
}
