// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0016C280: port of Sly 2 func_00151C38 (src/hand) with Sly 3 addresses; camera is p->pcm, positions via the LO vtable matrix.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M3 { qword r[3]; };
union M4 { struct { qword r[4]; } q; M3 m3; float af[4][4]; };
struct LO;
struct LOV { char pad[0x120]; short d; short p; M4 *(*pfnMat)(LO *); };
struct LO { int a[3]; LOV *pvt; };
struct CM;
struct CLQ { float g0, g1, g2, pad; };
struct LM { float gMin, gMax; int pad[2]; };
static const CLQ s_clq1 = { 200.0f, 0.22f, 0.0f };
static const LM s_lm1 = { 225.0f, 650.0f };
static const CLQ s_clq2 = { 600.0f, 0.33f, 0.0f };
static const LM s_lm2 = { 600.0f, 1500.0f };
static const CLQ s_clq3 = { 200.0f, 0.225f, 0.0f };
static const LM s_lm3 = { 0.0f, 500.0f };
static const CLQ s_clq4 = { 0.6f, 0.00045f, 0.0f };
static const LM s_lm4 = { 0.7f, 1.2f };
extern "C" qword D_00317550;
struct X { CM *pcm; char pad[0x1C]; LO *p20; LO *p24; };
static inline M4 *VMat(LO *plo) { return plo->pvt->pfnMat((LO *)((char *)plo + plo->pvt->d)); }
static inline qword Pos(LO *plo) { qword v = VMat(plo)->q.r[3]; return v; }
extern "C" {
void func_00169E78(X *p);
M3 *func_0011CBA0(M3 *pm, qword v);
qword *func_002BA818(qword *p, qword v);
void func_00166DE8(CM *p, M4 *m);
void func_00167960(CM *p, float g);
void func_0016C280(X *p);
}
static inline float GFromClq(const CLQ &c, float g) { return c.g0 + g * (c.g1 + g * c.g2); }
static inline float GClampR(float g, float lo, float hi) { if (g < lo) return lo; if (hi < g) return hi; return g; }
static inline float GClamp(float g, float lo, float hi) { if (g < lo) g = lo; else if (g > hi) g = hi; return g; }
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); } VU_FLOAT(const float &f, int) { __asm__("lw %0, %1" : "=r"(q) : "m"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword VecCombo(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q), "j"(f1.q), "j"(f2.q)); /* extra unused operands: allocation only */
    return r;
}
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Add(qword a, qword b) { qword d; __asm__("vadd.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline float Length(qword a)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(d), "=&j"(one) : "j"(a), "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline qword Cross(qword a, qword b)
{
    qword r;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b), "j"(a)); /* extra operand: allocation only */
    return r;
}
static inline qword Normalize(qword a)
{
    qword d, one, r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(d), "=&j"(one) : "j"(a));
    qword l;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(a), "j"(l));
    return r;
}
struct VU_FLOATJ { qword q; VU_FLOATJ(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
static inline qword Scale(qword a, VU_FLOATJ s) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s.q)); return r; }

void func_0016C280(X *p)
{
    U d;
    func_00169E78(p);
    d.q = Sub(Pos(p->p20), Pos(p->p24));
    d.f[2] = 0.0f;
    float dist = Length(d.q);
    U focus;
    focus.q = VecCombo(VU_FLOAT(0.45f), VU_VECTOR(Pos(p->p20)), VU_FLOAT(1.0f - 0.45f), VU_VECTOR(Pos(p->p24)));
    focus.f[2] = 150.0f;
    U pos;
    pos.q = focus.q;
    pos.f[2] += GClampR(GFromClq(s_clq1, dist), s_lm1.gMin, s_lm1.gMax);
    qword n = Normalize(Cross(d.q, D_00317550));
    float g = GClamp(GFromClq(s_clq2, dist), s_lm2.gMin, s_lm2.gMax);
    U pos2;
    pos2.q = Add(focus.q, Scale(n, VU_FLOATJ(g)));
    pos2.f[2] += GClamp(GFromClq(s_clq3, dist), s_lm3.gMin, s_lm3.gMax);
    {
        M4 m4;
        M3 m3;
        func_0011CBA0(&m3, Sub(pos.q, pos2.q));
        M4 *pm4 = &m4;
        func_002BA818(&pm4->q.r[3], pos2.q);
        pm4->q.r[0] = m3.r[0];
        pm4->q.r[1] = m3.r[1];
        pm4->q.r[2] = m3.r[2];
        m4.af[2][3] = 0.0f;
        m4.af[1][3] = 0.0f;
        m4.af[0][3] = 0.0f;
        pm4->af[3][3] = 1.0f;
        func_00166DE8(p->pcm, pm4);
    }
    func_00167960(p->pcm, GClamp(GFromClq(s_clq4, dist), s_lm4.gMin, s_lm4.gMax));
}
