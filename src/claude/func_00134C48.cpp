// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Three-point rig update: advance the spin angle, rebuild the basis from the blend of the target direction and the
// scaled up vector, then place three points on a circle around the axis; the selected one is probed against the
// world (func_00134758), the others are pushed onto their stored planes.
// Matching notes: the up vector is caller-saved across func_00134BE8 (save slot after the spill slots) only when it
// has enough refs, hence the allocation-only "j"(v2) operands of VecCombo; LenQ's allocation-only "j"(one) operands
// raise the unit lane's local-alloc priority so it takes vf1 and the dot vf2. i and pl are initialised early.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M3 { U r[3]; };
struct XF { char pad[0x30]; qword pos; };
struct VTE { short delta, pad; XF *(*fn)(void *); };
struct LO { char pad[0xC]; VTE *vt; };
struct ALO { char pad[0xDC]; int k; };
struct CLIPD { char pad[0x64]; float dur; };
struct CLIP { char pad[0x14]; CLIPD *pd; char pad18[4]; float t; };
struct SRC { char pad[0x40]; void *pclip; };
struct S {
    char pad0[0x10];
    ALO *palo;
    char pad14[4];
    SRC *psrc;
    char pad1C[0x38 - 0x1C];
    LO *ptarget;
    char pad3C[4];
    float ang;
    int index;
    char pad48[8];
    U planes[3];
    M3 basis;
    qword pos;
    qword pts[3];
};
struct SCALAR;
extern "C" SCALAR *func_002BA000(SCALAR *);
struct SCALAR { qword q; SCALAR() { (void)func_002BA000(this); } };
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); }
};
extern float D_0036BB9C;
extern "C" {
int func_00134AB8(S *);
CLIP *func_00254F80(void *);
float func_00134B98(S *, float);
float func_0011E3B8(float);
qword func_00134FF8(S *);
qword func_00135080(S *);
float func_00134BE8(S *, float);
void func_0011CBA0(M3 *, qword);
float func_00134B48(S *, float);
float cosf(float);
float sinf(float);
int func_0011E9C8(float, float, float);
qword func_00134758(qword, qword, int, U *);
void func_00134C48(S *p);
}
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Add(qword a, qword b)
{
    qword r;
    __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Dot(qword a, qword b)
{
    qword r, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
            : "=j"(r), "=j"(one) : "j"(a), "j"(b));
    return r;
}
static inline qword Root(qword a)
{
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(a));
    return a;
}
static inline qword MulX(qword v, qword s)
{
    qword r;
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(s));
    return r;
}
static inline qword Scale(qword v, VU_FLOAT s)
{
    qword r;
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(s.q));
    return r;
}
static inline qword LenQ(qword a)
{
    qword r, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
            : "=j"(r), "=j"(one) : "j"(a), "j"(a));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(r) : "j"(one), "j"(one), "j"(one));
    return r;
}
static inline qword ScaleS(qword v, VU_FLOAT s)
{
    qword r = s.q;
    __asm__("vmulx.xyzw %0,%1,%0x" : "+j"(r) : "j"(v));
    return r;
}
static inline qword VecCombo(VU_FLOAT f1, qword v1, VU_FLOAT f2, qword v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.q), "j"(v1), "j"(f2.q), "j"(v2), "j"(v2), "j"(v2), "j"(v2));
    return r;
}
static inline qword Rotate(const M3 &m, qword v)
{
    __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z"
            : "+j"(v) : "j"(m.r[0].q), "j"(m.r[1].q), "j"(m.r[2].q));
    return v;
}
static inline float ToFloatR(qword v) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(v)); return f; }
static inline float PlaneDist(qword plane, qword pos)
{
    SCALAR dot, one;
    qword r, unit;
    float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(r), "=&j"(unit) : "j"(plane), "j"(pos));
    dot.q = r;
    one.q = unit;
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(dot.q), "j"(r));
    return f;
}
static inline XF *PxfGet(LO *p) { return p->vt[36].fn((char *)p + p->vt[36].delta); }

void func_00134C48(S *p)
{
    if (!func_00134AB8(p))
        return;
    float t = 1.0f;
    if (p->psrc && p->psrc->pclip) {
        CLIP *c = func_00254F80(p->psrc->pclip);
        if (c)
            t = c->t / c->pd->dur;
    }
    float k = D_0036BB9C;
    int i = 0;
    U *pl = p->planes;
    p->ang = func_0011E3B8(p->ang + k * func_00134B98(p, t));
    p->pos = func_00134FF8(p);
    qword dir = Sub(PxfGet(p->ptarget)->pos, p->pos);
    qword up = MulX(func_00135080(p), LenQ(dir));
    float g = func_00134BE8(p, t);
    qword axis = VecCombo(VU_FLOAT(g), dir, VU_FLOAT(1.0f - g), up);
    {
        M3 basis;
        func_0011CBA0(&basis, axis);
        p->basis = basis;
    }
    float r = func_00134B48(p, t);
    float ang = p->ang;
    for (; i < 3; i++, pl++) {
        U off;
        {
            U v;
            v.q = 0;
            v.f[1] = cosf(ang);
            v.f[2] = sinf(ang);
            off = v;
        }
        off.q = Add(axis, ScaleS(Rotate(p->basis, off.q), VU_FLOAT(r)));
        if (i == p->index) {
            float len = ToFloatR(Root(Dot(axis, axis)));
            if (0.0f < len)
                off.q = Scale(off.q, VU_FLOAT((len + 2000.0f) / len));
            pl[7].q = func_00134758(p->pos, Add(p->pos, off.q), p->palo->k, pl);
        } else {
            float z = 0.0f;
            float d = -PlaneDist(pl->q, p->pos);
            float dn = ToFloatR(Dot(pl->q, off.q));
            if (!func_0011E9C8(dn, z, 0.0001f)) {
                float s = d / dn;
                if (z <= s)
                    off.q = Scale(off.q, VU_FLOAT(s));
            }
            pl[7].q = Add(p->pos, off.q);
        }
        ang += 2.0943952f;
    }
}
