// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct O;
struct M { short delta, pad; qword (*fn)(void *); };
struct VT { char pad[0x130]; struct M m; };
struct D8 { char pad[0x80]; qword v; };
struct O { char pad[0xC]; struct VT *vt; char pad1[0xD8 - 0x10]; struct D8 *pD8; char pad2[0x1A0 - 0xDC]; qword v1A0;
    char pad3[0x438 - 0x1B0]; struct O *p438; char pad4[0x440 - 0x43C]; qword v440; };
struct P { struct O *po; char pad[0x34 - 4]; int x34; };
extern qword D_00317560;
extern int D_0036BB9C;
int func_002503C8(struct O *po, float g);
qword func_001C94E8(struct O *po, int n, qword v);
void func_00244828(struct O *po, qword v);
qword func_001205F0(qword v, float gMax);
static inline qword Method(struct O *po) { struct M *m = &po->vt->m; return m->fn((char *)po + m->delta); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Mul(qword a, qword b) { qword r; __asm__("vmul.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword MulX(qword a, qword b) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword SplatI(int g) { qword r; __asm__("qmtc2.ni %1, %0" : "=j"(r) : "r"(g)); return r; }
static inline qword Splat(float g) { qword r; __asm__("qmtc2.ni %1, %0" : "=j"(r) : "r"(g)); return r; }
static inline qword DivX(qword a, qword b)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(b), "j"(a));
    return r;
}
void func_0013A9E0(struct P *p)
{
    U a, c, s;
    qword b;
    struct O *po;
    if (!func_002503C8(p->po, 0.1f))
        return;
    a.q = Method(p->po);
    po = p->po;
    if (po->p438) {
        qword v = po->v440;
        b = Mul(v, Method(po->p438));
    } else
        b = D_00317560;
    c.q = Sub(b, func_001C94E8(p->po, 0, p->po->v1A0));
    if (p->x34) {
        struct O *o = p->po;
        qword v = o->pD8->v;
        s.q = Splat(-1.0f);
        func_00244828(o, MulX(v, s.q));
    } else
        c.f[2] = a.f[2];
    s.q = SplatI(D_0036BB9C);
    func_00244828(p->po, func_001205F0(DivX(Sub(c.q, a.q), s.q), 2000.0f));
}
