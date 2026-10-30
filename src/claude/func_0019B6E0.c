// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the Sly 2 decomp (func_0017F1D0): apply damage and a projected knockback impulse from the message.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct P;
struct VT { short d, pad; void *fn; };
struct SPS { int kind; };
struct O;
struct Q { char pad[0xB0]; char s[0xC0 - 0xB0]; int kind; };
struct P {
    char pad[0xC]; struct VT *vt;
    char pad10[0x48 - 0x10]; struct O *x48;
    char pad4C[0xD8 - 0x4C]; struct Q *xD8;
    char padDC[0x180 - 0xDC]; int n180;
    char pad184[0x1B0 - 0x184]; float g0, g1, g2, g3, gMin, gMax;
};
struct MSG { char pad[0x14]; void *x14; char pad18[0x20 - 0x18]; void *x20; int delta; int x28; char pad2C[4]; qword pos; char pad40[0x50 - 0x40]; int flags; };
extern qword D_00317550, D_00317530;
void func_001F4DD8(struct P *, void *, void *, float);
void func_001F43D0(struct P *, int);
int func_001F43C8(struct P *);
qword func_001205F0(qword, float);
qword func_00244418(void *, struct O *, qword);
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Reject(qword a, qword n) { qword d, one; __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(d), "=&j"(one) : "j"(a), "j"(n)); __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(d) : "j"(n), "j"(d)); return Sub(a, d); }
/* the one register pin: the normalized result lives in vf1 on both paths (fallback copy and vmulq) */
static inline qword Normal(qword a, qword fallback) { register qword d __asm__("vf1"); qword one; float len; __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(d), "=&j"(one) : "j"(a)); __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "j"(d)); __asm__("qmfc2.ni %0,%1" : "=r"(len) : "j"(d)); if (len < 0.0001f) { d = fallback; } else { __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(d) : "j"(d), "j"(a)); } return d; }
static inline qword AddScaled(qword a, qword b, float g) { qword k; U u; __asm__("qmtc2.ni %1,%0" : "=j"(k) : "r"(g)); u.q = k; __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x" : "=j"(a) : "j"(b), "j"(k), "0"(a)); return a; }
static inline float Clamp(float g, float lo, float hi) { if (g < lo) return lo; if (hi < g) return hi; return g; }
int func_0019B6E0(struct P *p, struct MSG *m)
{
    qword dir, v;
    float g, t;
    if (!(m->flags & 2) || p->n180)
        return 0;
    func_001F4DD8(p, m->x14, m->x20, -3.40282347e+38f);
    if (m->x28)
        func_001F43D0(p, 0);
    else
        func_001F43D0(p, func_001F43C8(p) - m->delta);
    if (func_001F43C8(p) <= 0) {
        struct VT *vt = p->vt;
        ((void (*)(struct P *, int))vt[92].fn)((struct P *)((char *)p + vt[92].d), 0);
        return 1;
    }
    if (!p->xD8 || p->xD8->kind == 3)
        return 1;
    {
        struct VT *vt = p->vt;
        qword pos = ((U *(*)(struct P *))vt[36].fn)((struct P *)((char *)p + vt[36].d))[3].q;
        dir = Normal(Reject(Sub(pos, m->pos), D_00317550), D_00317530);
    }
    { float *a = &p->g0; t = m->delta; g = Clamp(p->g0 + t * (a[1] + t * a[2]), p->gMin, p->gMax); }
    { struct VT *vt = p->vt; v = ((qword (*)(struct P *))vt[38].fn)((struct P *)((char *)p + vt[38].d)); }
    v = func_001205F0(AddScaled(v, dir, g), p->gMax);
    v = func_00244418(p->xD8->s, p->x48, v);
    { struct VT *vt = p->vt; ((void (*)(struct P *, qword))vt[40].fn)((struct P *)((char *)p + vt[40].d), v); }
    return 1;
}
