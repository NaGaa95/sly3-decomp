// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// func_0019F9C8 (A48): from A24 f9c8_f.cpp; keys: func_002BA818 returns qword* (sched2 dependents), VU_FLOAT(0.5f) temporaries per QwCombine arg + VU_VECTOR params, if/else GSmooth calls, Length via mtc1 asm (gcc qmfc2), stores of the M3 rows and r[3].w through pm = &mat.
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta, pad; void *fn; };
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
union U { qword q; float f[4]; };
struct SMP { float a, b, c; };
struct LO { char pad0[0xC]; VTE *vt; char pad10[0x118 - 0x10]; float f118; char pad11C[0x2F4 - 0x11C]; int n2F4; char pad2F8[0x310 - 0x2F8]; char curve[1]; };
struct VU_FLOAT {
    qword qw;
    VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=r"(qw) : "f"(f)); }
};
struct VU_FLOATJ {
    qword qw;
    VU_FLOATJ(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "r"(f)); }
};
struct OBJ {
    LO *plo0;
    char pad4[0x20 - 4];
    LO *ploA;
    LO *ploB;
    char pad28[0x30 - 0x28];
    qword pos;
    float g40;
};
struct CLOCK { float t, dt; };
static const SMP s_smpPos = { 500.0f, 0.0f, 1.0f };
static const SMP s_smpUp = { 250.0f, 0.25f, 0.5f };
static const SMP s_smpDown = { 500.0f, 0.0f, 0.5f };
extern "C" {
extern CLOCK g_clock;
extern qword D_00317530;
void func_00169E78(OBJ *p);
qword func_00120C80(qword pos, qword goal, const SMP *psmp, int n, float dt);
float func_002A3160(float);
float func_0011EE68(void *curve, float u);
float GSmooth(float g, float gGoal, float dt, const SMP *psmp, float *pdv) __asm__("GSmooth__FfffP3SMPPf");
M3 func_0011CBA0(qword dir);
qword *func_002BA818(qword *pdst, qword v);
void func_00166DE8(LO *plo, M4 *pmat);
void func_0019F9C8(OBJ *p);
}
static inline qword PosOf(LO *p)
{
    VTE *e = &p->vt[36];
    return ((M4 *(*)(void *))e->fn)((char *)p + e->delta)->r[3];
}
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword QwCombine(VU_FLOAT g0, VU_VECTOR a, VU_FLOAT g1, VU_VECTOR b)
{
    qword qw;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(qw) : "j"(g0.qw), "j"(a.q), "j"(g1.qw), "j"(b.q));
    return qw;
}
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwAdd(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwScale(qword v, VU_FLOATJ g) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(g.qw)); return r; }
static inline float Length(qword v)
{
    qword d, one;
    float f;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(d));
    return f;
}

void func_0019F9C8(OBJ *p)
{
    func_00169E78(p);
    U d;
    d.q = QwSub(PosOf(p->ploA), PosOf(p->ploB));
    d.f[2] = 0.0f;
    float len = Length(d.q);
    U mid;
    mid.q = QwCombine(VU_FLOAT(0.5f), PosOf(p->ploA), VU_FLOAT(0.5f), PosOf(p->ploB));
    if (p->plo0->n2F4)
        p->pos = mid.q;
    p->pos = func_00120C80(p->pos, mid.q, &s_smpPos, 0, g_clock.dt);
    U pos, below;
    pos.q = p->pos;
    below.q = QwAdd(pos.q, QwScale(D_00317530, VU_FLOATJ(-500.0f)));
    float t = func_002A3160(p->plo0->f118 * 0.5f);
    float g = func_0011EE68(p->ploA->curve, (len + 250.0f) / t);
    float cur = p->g40;
    if (g < cur)
        g = GSmooth(cur, g, g_clock.dt, &s_smpUp, 0);
    else
        g = GSmooth(cur, g, g_clock.dt, &s_smpDown, 0);
    p->g40 = g;
    below.f[2] += g;
    M4 mat;
    M3 m;
    m = func_0011CBA0(QwSub(pos.q, below.q));
    func_002BA818(&mat.r[3], below.q);
    M4 *pm = &mat;
    pm->r[0] = m.r[0];
    pm->r[1] = m.r[1];
    pm->r[2] = m.r[2];
    ((U *)&mat.r[2])->f[3] = 0.0f;
    ((U *)&mat.r[1])->f[3] = 0.0f;
    ((U *)&mat.r[0])->f[3] = 0.0f;
    ((U *)&pm->r[3])->f[3] = 1.0f;
    func_00166DE8(p->plo0, &mat);
}
