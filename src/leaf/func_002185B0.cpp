// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_ASFIX: engine-divfix1
typedef unsigned long long qword __attribute__((mode(TI)));
struct VE { short delta, pad; void *fn; };
union VU { qword q; float f[4]; };
struct M4 { qword r[4]; };
struct LM { float gMin, gMax; };
struct POLY { float c0, c1, c2; };
struct OBJ;
struct LINK { OBJ *obj; };
struct OBJ
{
    char pad0[0xC]; VE *vt; int pad10; LINK *link;
    char pad18[0x220 - 0x18]; float width;
    char pad224[0x260 - 0x224]; int side;
    char pad264[0x3C8 - 0x264]; void *source; int pad3CC; float range;
    char pad3D4[0x3E0 - 0x3D4]; POLY poly;
    char pad3EC[0x3F0 - 0x3EC]; float limA; float limB;
    char pad3F8[0x41C - 0x3F8]; OBJ *other[2];
    char pad424[0x4F4 - 0x424]; int kind;
};
struct REQ { void *p0; OBJ *target; char pad8[0x10 - 8]; int kind; };
extern qword D_00317530;
extern LM D_00341FF0;
extern "C" {
OBJ *func_001FBE30(void *, int);
void func_001C7A00(OBJ *, int, int);
void func_001C8FB0(OBJ *, OBJ *);
int func_0013B500(void *, int);
void func_0014D1F0(OBJ *, OBJ *);
void func_0023EC98(OBJ *, int);
qword func_001C9428(OBJ *, OBJ *, qword);
float func_0011EE68(LM *, float);
void func_0028F680(void *, int, M4 *, float, int);
M4 func_0011D558(const M4 &, const M4 &);
float func_001205C8(qword);
float func_0011E3B8(float);
float func_002A36E8(float);
qword func_0023ED38(OBJ *);
qword func_00212628(qword, qword, qword, float);
}
static inline M4 *Matrix(OBJ *o) { VE *v = &o->vt[36]; return ((M4 *(*)(void *))v->fn)((char *)o + v->delta); }
static inline void *Frame(OBJ *o, M4 *pm) { VE *v = &o->vt[37]; return ((void *(*)(void *, M4 *))v->fn)((char *)o + v->delta, pm); }
static inline void Launch(OBJ *o, qword q) { VE *v = &o->vt[40]; ((void (*)(void *, qword))v->fn)((char *)o + v->delta, q); }
static inline qword QwSub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword QwZero() { qword d; __asm__("vsub.xyzw %0, $vf0, $vf0" : "=j"(d)); return d; }
static inline qword QwDot(qword a, qword b)
{
    qword qw, vfOne;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=j"(vfOne) : "j"(a), "j"(b));
    return qw;
}
static inline qword QwSqrt(qword qw) { qword qw2; __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw2) : "j"(qw)); return qw2; }
static inline qword QwLength(qword v)
{
    qword qw, qw2, vfOne;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=j"(vfOne) : "j"(v), "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw2) : "j"(qw));
    return qw2;
}
static inline qword QwLength2(qword v) { return QwSqrt(QwDot(v, v)); }
static inline float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline qword DivQ(qword qw, qword v)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(qw), "j"(v));
    return r;
}
static inline qword QwFromXYZ(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static inline qword Xform(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "0"(v));
    return r;
}
struct VF { qword q; VF(const float &g) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(const int *)&g)); } };
static inline qword Madd(qword a, VF s, qword b)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline qword Normalize(qword v, qword len, float l)
{
    qword fb = D_00317530;
    if (l < 1.0e-4f)
        return fb;
    return DivQ(len, v);
}
static inline qword Normalize2(qword v, qword len)
{
    if (F(len) < 1.0e-4f)
        return D_00317530;
    return DivQ(len, v);
}
static inline float GMin(float a, float b) { return a < b ? a : b; }
static inline float Poly(POLY *pp, float g) { return pp->c0 + g * (pp->c1 + g * pp->c2); }

extern "C" int func_002185B0(OBJ *p, REQ *req, int side)
{
    if (side == p->side)
        p->side = -1;
    if (!p->source || !req->p0 || !req->target || req->kind != 2)
        return 0;
    OBJ *o = func_001FBE30(p->source, 0);
    if (o)
    {
    func_001C7A00(o, 0, 0);
    func_001C8FB0(o, req->target);
    if (func_0013B500(o, 0x59))
    {
        func_0014D1F0(o, p);
        func_0023EC98(o, 1);
    }
    float range = p->range;
    if (p->kind == 0x42)
        range *= 1.5f;
    OBJ *other = p->other[side];
    float dist;
    if (other)
    {
        qword pos = Matrix(o)->r[3];
        dist = F(QwLength(QwSub(pos, Matrix(other)->r[3])));
        dist = GMin(dist, range);
    }
    else
        dist = range;
    float g = Poly(&p->poly, dist);
    qword local = func_001C9428(0, p, Matrix(req->target)->r[3]);
    M4 frame;
    qword v;
    void *pf;
    if (other)
    {
        v = QwZero();
        pf = Frame(other, &frame);
        if (func_0013B500(other->link->obj, 0x58))
        {
            OBJ *q = other->link->obj;
            float half = q->width * 0.5f;
            float u = func_0011EE68(&D_00341FF0, F(local) / p->width + 0.5f);
            qword r0 = Matrix(p)->r[0];
            if (F(QwDot(r0, Matrix(q)->r[0])) < 0.0f)
                u = 1.0f - u;
            VU t;
            t.q = QwFromXYZ((1.0f - u) * -half + u * half, 0.0f, 0.0f);
            v = t.q;
        }
    }
    else
    {
        pf = Frame(req->target, &frame);
        VU t;
        t.q = QwFromXYZ(dist, 0.0f, 0.0f);
        v = t.q;
    }
    M4 m;
    func_0028F680(pf, 0, &m, g, 0);
    VU q;
    q.q = func_001C9428(0, req->target, Xform(func_0011D558(m, frame), v));
    LM lm;
    if (other)
    {
        int f = 0;
        switch (side)
        {
        case 0:
            f = F(local) < 0.0f;
            break;
        case 1:
            f = F(local) > 0.0f;
            break;
        }
        if (f)
        {
            lm.gMin = -p->limB;
            lm.gMax = p->limA;
        }
        else
        {
            lm.gMin = -p->limA;
            lm.gMax = p->limB;
        }
    }
    else
    {
        lm.gMin = 0.0f;
        lm.gMax = 0.0f;
    }
    float a = func_0011EE68(&lm, func_0011E3B8(func_001205C8(q.q)));
    float x = q.f[0];
    q.f[1] = x * func_002A36E8(a);
    qword r = func_001C9428(req->target, 0, q.q);
    qword d = QwSub(r, Matrix(req->target)->r[3]);
    qword len = QwLength(d);
    float l = F(len);
    range = GMin(l, range);
    qword pos = Matrix(req->target)->r[3];
    VF s(range);
    r = Madd(pos, s, Normalize(d, len, l));
    Launch(o, func_00212628(Matrix(o)->r[3], r, func_0023ED38(o), g));
    return 1;
    }
    return 0;
}
