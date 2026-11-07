// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00252508: sibling of func_00232710 / func_001479A0 (light pass of an object). When the object's mask intersects the scene light
// mask, the scene returns per-light weights for the object position; every light slot of link kind 2 is drawn once through a scale
// matrix (distance attenuation from the scene block at +0x4E00, plus a sine wobble for 0.85s after the time at +0x380, curve D_003273E0,
// blend D_003273F0) conjugated by the model matrix at p50+0x40 into p+0x1780; remaining weights are drawn together at the end.
// Matching notes: p->m1780 product order uses an early &r pointer (s3), m33 is set through the identity pointer, hi/lo assignment order.
typedef int qword __attribute__((mode(TI)));
union M4 { qword r[4]; float m[4][4]; };
struct VTE { short d; short pad; void *pfn; };
struct LO;
struct DZ { char pad[8]; int n8; };
struct LO {
    char pad0[0xC]; VTE *pvt; char pad10[0x2C - 0x10]; unsigned char b2C; char pad2D[0x34 - 0x2D]; float g34;
    char pad38[0x50 - 0x38]; char *p50; char pad54[0x70 - 0x54]; char a70[0x10]; qword v80; float g90;
    char pad94[0x104 - 0x94]; float g104; int pad108; int n10C; char pad110[0x250 - 0x110]; float g250, g254, g258;
    char pad25C[0x29C - 0x25C]; char a29C[0x300 - 0x29C]; DZ *p300; char pad304[0x380 - 0x304]; float g380;
    char pad384[0x1154 - 0x384]; float g1154; char pad1158[0x1780 - 0x1158]; M4 m1780;
};
struct SW { char pad[0x3E04]; int grfMask; char pad3E08[0x3EB8 - 0x3E08]; int cso; LO *apso[5]; qword q3ED0;
    char pad3EE0[0x4E00 - 0x3EE0]; float ac[3]; float pad4E0C; float gMin, gMax; };
struct CLOCK { float t; float dt; };
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
union U { qword q; float f[4]; };
extern CLOCK g_clock;
extern "C" {
extern SW D_00475480;
extern float D_003273E0[3];
extern float D_003273F0[2];
extern struct LM { float gMin, gMax; } D_00341FF0;
void func_0023CBE0(LO *);
qword func_0011D5C8(M4 *, qword);
qword func_0018E500(SW *psw, qword q, int k, qword v, float g);
void *memset(void *, int, unsigned int);
qword *func_002BA818(qword *, qword);
M4 *func_0011D558(M4 *, const M4 *, const M4 *);
void func_0011D768(M4 *, const M4 *);
qword func_001C8548(int);
void func_0018E800(void *, qword, M4 *, int, float, float);
void func_00238908(void *);
float sinf(float);
void func_00252508(LO *p);
}
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("lw %0, %1" : "=rj"(q) : "m"(f)); } };
static inline M4 *Matrix(LO *p) { VTE *e = &p->pvt[36]; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
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
static inline int IsZero(qword v)
{
    int mac;
    __asm__("vadd.xyzw $vf0, %1, %1\n\tvnop\n\tvnop\n\tvnop\n\tvnop\n\tcfc2.ni %0, $vi17" : "=r"(mac) : "j"(v));
    return ((mac & 0xF) ^ 0xF) == 0;
}
// The second "j"(a) operand is allocation-only: it raises a's local-alloc priority so a stays in vf1 like the game.
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b), "j"(a)); return r; }
static inline float Length(qword v)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline void SetIdentity(M4 *pm)
{
    float *f = (float *)pm;
    memset(pm, 0, sizeof(M4));
    f[0] = f[5] = f[10] = f[15] = 1.0f;
}
static inline float GLerp(const float *a, float s) { return (1.0f - s) * a[0] + s * a[1]; }
static inline float GPoly(const float *a, float x) { return a[0] + x * (a[1] + x * a[2]); }
static inline float GClamp(const LM *plm, float g) { float lo = plm->gMin, hi = plm->gMax; float r; if (g < lo) r = lo; else if (hi < g) r = hi; else r = g; return r; }
static inline float Clamp(float g, float lo, float hi) { float r; if (g < lo) r = lo; else if (hi < g) r = hi; else r = g; return r; }

void func_00252508(LO *p)
{
    if (!(p->b2C & D_00475480.grfMask))
        return;
    U hit;
    func_0023CBE0(p);
    qword pos = p->v80;
    float w = GetX(VU_FLOAT(p->g90).q);
    qword v = VU_VECTOR(GetX(pos), GetY(pos), GetZ(pos), w).q;
    v = func_0011D5C8(Matrix(p), v);
    hit.q = func_0018E500(&D_00475480, D_00475480.q3ED0, p->b2C, v, p->g34);
    SetIdentity(&p->m1780);
    if (!IsZero(hit.q))
        p->g1154 = g_clock.t;
    for (int i = 0; i < D_00475480.cso; i++) {
        if (hit.f[i] == 0.0f)
            continue;
        LO *o = D_00475480.apso[i];
        if (!o->p300 || o->p300->n8 != 2)
            continue;
        hit.f[i] = 0.0f;
        M4 m;
        M4 *pm = &m;
        SetIdentity(pm);
        qword a = Matrix(p)->r[3];
        float d = Length(Sub(a, Matrix(o)->r[3]));
        float s = Clamp(GPoly(D_00475480.ac, d), D_00475480.gMin, D_00475480.gMax);
        float t = g_clock.t - p->g380;
        float lo, hi;
        lo = hi = s;
        if (t < 0.85f) {
            float sn = (sinf(t * 80.0f) + 1.0f) * 0.5f;
            float u = t * 1.17647052f;
            float w = GLerp(D_003273F0, sn) * GClamp(&D_00341FF0, GPoly(D_003273E0, u));
            lo = s - w;
            hi = s + w;
        }
        m.m[0][0] = lo;
        m.m[1][1] = lo;
        m.m[2][2] = hi;
        VECTOR4 tr;
        tr.x = (1.0f - lo) * p->g250;
        tr.y = (1.0f - lo) * p->g254;
        tr.z = (1.0f - hi) * p->g258;
        func_002BA818(&m.r[3], *(qword *)&tr);
        pm->m[3][3] = 1.0f;
        M4 c = *(M4 *)(p->p50 + 0x40);
        M4 r, cm, ci;
        M4 *pr = &r;
        func_0011D558(&cm, &c, &m);
        func_0011D768(&ci, &c);
        func_0011D558(pr, &cm, &ci);
        p->m1780 = r;
        func_0018E800(p->a70, func_001C8548(i), &p->m1780, p->n10C, p->g104, p->g104);
    }
    if (!IsZero(hit.q))
        func_0018E800(p->a70, hit.q, 0, p->n10C, p->g104, p->g104);
    func_00238908(p->a29C);
}
