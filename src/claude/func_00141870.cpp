// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00141870 (A25/A25b layout, finished by A30): smoothed euler target -> rotation, angular velocity of p4C, and the
// position correction pushed through func_00244828. Keys (A30): both VU_FLOAT(g_clock.dt) use the func_00151340 ctor
// with a "r,V" word input (gcc-generated lw, tied to the dying &g_clock reg) as by-value temporaries (second one gets
// its own home at 0xF0), vB0 read into a local before the VU_FLOAT temp and vF0 by const reference after it.
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct VECTOR { float x, y, z; };
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
struct SMP { float svFast, svSlow, dtFast; };
struct VTE { short d; short pad; void *pfn; };
struct XF { char pad[0xA0]; XF *pxfParent; char padA4[0xB0 - 0xA4]; VECTOR4 vB0; char padC0[0xF0 - 0xC0]; VECTOR4 vF0; };
struct P {
    char pad0[0xC]; VTE *pvt; char pad10[0x48 - 0x10]; XF *p48; XF *p4C;
    char pad50[0x198 - 0x50]; int x198; char pad19C[0x1A8 - 0x19C]; float g1A8;
    char pad1AC[0x1BC - 0x1AC]; SMP asmp[3]; VECTOR4 v1E0; float g1F0;
    char pad1F4[0x2B0 - 0x1F4]; int x2B0; float g2B4; int x2B8; char pad2BC[0x2D8 - 0x2BC]; int x2D8;
    char pad2DC[0x400 - 0x2DC]; float g400; float g404; float g408; float g40C; char pad410[0x418 - 0x410]; int x418;
};
struct VU_VECTOR { qword q; VU_VECTOR() {} VU_VECTOR(const qword &v) { q = v; } };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } VU_FLOAT(const float *pg) { __asm__("qmtc2.ni %1, %0" : "=j,j"(q) : "r,V"(*(const int *)pg)); } };
extern "C" {
extern struct CLOCK { float t; float dt; } g_clock;
void func_00243738(P *p);
qword func_0011D3C0(void *pm);
float func_0011E840(float gCur, float gTarget, float dt, SMP *psmp, float *pdg);
M3 func_0011C9E8(qword v);
M3 func_0028EA00(XF *a, XF *b, const M3 &m);
M3 func_0011CFC0(XF *a, const M3 &m);
VU_VECTOR func_0028E990(XF *a, XF *b, VU_VECTOR v);
VU_VECTOR func_001205F0(VU_VECTOR v, float g);
void func_00244828(P *p, VU_VECTOR v);
void DecomposeRotateMatrixRad__FP7MATRIX3PfP6VECTOR(M3 *pm, float *pg, VECTOR4 *pv);
}
#define Q(v) (*(qword *)&(v))
static inline void *Matrix(P *p) { VTE *e = &p->pvt[36]; return ((void *(*)(void *))e->pfn)((char *)p + e->d); }
static inline qword operator*(VU_VECTOR v, VU_FLOAT f)
{ qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v.q), "j"(f.q)); return r; }
static inline qword AddScale(qword a, qword b, VU_FLOAT f)
{ qword r; __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(f.q)); return r; }
static inline qword operator*(const M3 &m, const VECTOR4 &v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(r) : "j"(*(qword *)&v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return r;
}
static inline qword Sub(qword a, qword b)
{ qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Div(qword a, VU_FLOAT f)
{ qword r; __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(a), "j"(f.q)); return r; }

static inline qword MulAdd2(const qword &a, VU_FLOAT f, qword b)
{ qword r; __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(b), "j"(a), "j"(f.q)); return r; }
extern "C" void func_00141870(P *p)
{
    SMP smp;
    VECTOR4 vec;
    M3 matA;
    M3 matC;
    VECTOR4 axis;
    float g;
    func_00243738(p);
    switch (p->x198) {
    case 3:
        return;
    case 0:
        if (p->x2B0 == 2)
            return;
        if (p->x2B8 && !p->x2D8)
            return;
    }
    if (p->x2B0 == 4 && g_clock.t - p->g2B4 < p->g1F0)
        return;
    smp = p->asmp[2];
    if (p->x198 == 0 && p->x2B0 == 1 && p->x418)
        smp.svFast *= 1.5f;
    *(qword *)&p->v1E0 = func_0011D3C0(Matrix(p));
    vec.x = func_0011E840(p->v1E0.x, p->g404, g_clock.dt, &p->asmp[0], 0);
    if (p->x2D8)
        vec.y = p->g408;
    else
        vec.y = func_0011E840(p->v1E0.y, p->g408, g_clock.dt, &p->asmp[1], 0);
    vec.z = func_0011E840(p->v1E0.z, p->g40C, g_clock.dt, &smp, 0);
    matA = func_0011C9E8(*(qword *)&vec);
    matA = func_0028EA00(0, p->p4C->pxfParent, matA);
    matC = func_0011CFC0(p->p4C, matA);
    DecomposeRotateMatrixRad__FP7MATRIX3PfP6VECTOR(&matC, &g, &axis);
    Q(p->p4C->vB0) = (VU_VECTOR(*(qword *)&axis) * VU_FLOAT(g / g_clock.dt));
    XF *pxf = p->p48;
    qword b = Q(pxf->vB0);
    VECTOR4 v;
    Q(v) = MulAdd2(Q(pxf->vF0), VU_FLOAT(&g_clock.dt), b);
    VECTOR4 w;
    Q(w) = func_0028E990(pxf->pxfParent, p->p4C, Q(v)).q;
    VECTOR4 t;
    VECTOR4 d, f, e;
    t.x = p->g400;
    t.y = 0.0f;
    t.z = 0.0f;
    Q(t) = matC * t;
    Q(d) = Div(Sub(Q(t), Q(w)), VU_FLOAT(&g_clock.dt));
    Q(e) = func_001205F0(Q(d), p->g1A8).q;
    Q(f) = func_0028E990(p->p4C, 0, Q(e)).q;
    func_00244828(p, Q(f));
}
