// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00162370: frame the target box on screen (scale + offset for func_00262848).
// The unit's .rodata (corner table 0x320B50, LM 0x320BD0) is defined here with external linkage so g++ emits it
// before the function's FLT_MAX literals, in the original order.
typedef int qword __attribute__((mode(TI)));
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
struct LM { float gMin, gMax; };
struct M4 { qword r[4]; };
struct LO;
struct LOV { char pad[0x120]; short d; short p; M4 *(*pfnMat)(LO *); };
struct LO { int a[3]; LOV *pvt; };
struct RECTI { int xMin, yMin, xMax, yMax; };
struct G { char pad[0x160]; RECTI rc; };
struct X { LO *plo; void *pv; int mode; float tStart; int x10; void *ptarget; int pad18[2]; float dt; };
struct SCR { int x0, cx, cy; };
struct XF { float a, b, c, d, tx, ty; };
extern "C" const VECTOR4 D_00320B50[8] = {
    { 50.0f, 50.0f, 100.0f, 0.0f }, { 50.0f, -50.0f, 100.0f, 0.0f }, { -50.0f, 50.0f, 100.0f, 0.0f }, { -50.0f, -50.0f, 100.0f, 0.0f },
    { 50.0f, 50.0f, -50.0f, 0.0f }, { 50.0f, -50.0f, -50.0f, 0.0f }, { -50.0f, 50.0f, -50.0f, 0.0f }, { -50.0f, -50.0f, -50.0f, 0.0f },
};
extern "C" const LM D_00320BD0 = { 0.25f, 1.25f };
extern "C" {
extern struct CLOCK { float t; } g_clock;
extern LM D_00341FF0;
extern qword D_00317560;
extern SCR D_0036DBE0;
G *func_001F4A80(void *p);
qword func_001678C8(G *pg, qword v);
qword func_001622C0(G *pg, qword v);
qword func_001C9428(LO *plo, int n, qword v);
float func_0011EE68(const LM *plm, float g);
void func_00262848(void *p, XF *pxf);
void func_00162370(X *p);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR {
    qword q;
    VU_VECTOR(float g) { qword t; __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(g), "f"(g), "f"(g)); }
};
static inline M4 *VMat(LO *plo) { return plo->pvt->pfnMat((LO *)((char *)plo + plo->pvt->d)); }
static inline qword Max(qword a, qword b) { qword d; __asm__("vmax.xyz %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Min(qword a, qword b) { qword d; __asm__("vmini.xyz %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline float LenXY(qword v)
{
    qword d;
    float g;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline qword Blend(qword a, VU_FLOAT s, qword b, VU_FLOAT t)
{
    qword d;
    __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(d) : "j"(a), "j"(s.q), "j"(b), "j"(t.q), "jm"(a)); /* extra operand: allocation only */
    return d;
}
static inline float PackedX(qword v) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(v)); return g; }
static inline float PackedY(qword v) { float g; __asm__("prot3w %0, %1" : "=r"(g) : "r"(v)); return g; }
static inline int Clamp(int g, int lo, int hi) { if (g < lo) return lo; if (hi < g) return hi; return g; }

void func_00162370(X *p)
{
    if (!p->ptarget)
        return;
    if (p->mode >= 3)
        return;
    if (p->mode <= 0)
        return;
    G *pg = func_001F4A80(p->pv);
    qword pos = func_001622C0(pg, func_001678C8(pg, VMat(p->plo)->r[3]));
    qword vMin = VU_VECTOR(3.40282347e+38f).q;
    qword vMax = VU_VECTOR(-3.40282347e+38f).q;
    for (unsigned int i = 0; i < 8; i++) {
        qword v = func_001622C0(pg, func_001678C8(pg, func_001C9428(p->plo, 0, *(const qword *)&D_00320B50[i])));
        vMin = Min(vMin, v);
        vMax = Max(vMax, v);
    }
    float gScale = func_0011EE68(&D_00320BD0, LenXY(Sub(vMin, vMax)) * 0.015f);
    if (p->mode == 1) {
        qword posCenter = func_001622C0(pg, D_00317560);
        float t = func_0011EE68(&D_00341FF0, (g_clock.t - p->tStart) / p->dt);
        pos = Blend(pos, VU_FLOAT(t), posCenter, VU_FLOAT(1.0f - t));
        gScale = (1.0f - t) * 3.5f + t * gScale;
    }
    RECTI *prc = &pg->rc;
    float x = (float)Clamp((int)PackedX(pos), prc->xMin, prc->xMax);
    float y = (float)Clamp((int)PackedY(pos), prc->yMin, prc->yMax);
    XF xf;
    xf.a = gScale;
    xf.b = 0.0f;
    xf.c = 0.0f;
    xf.d = gScale;
    float fcx = (float)D_0036DBE0.cx;
    float fcy = (float)D_0036DBE0.cy;
    float mx = x * 640.0f;
    float my = y * 480.0f;
    xf.tx = mx / fcx;
    xf.ty = my / fcy;
    func_00262848(p->ptarget, &xf);
}
