// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 2 reference: /home/claude/decomp src/hand/func_001507F8.c.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
typedef struct { qword r[3]; } M3;
struct VEntry { short delta; short pad; void *(*get)(void *); };
struct LO { char pad[0xC]; struct VEntry *table; };
struct X { char pad[0x24]; struct LO *p14; char pad1[0xB4 - 0x28]; float gA4; float gA8; };
typedef union { float f[4]; qword q; } K;
static const K s_offset = { { -50.0f, 0.0f, 0.0f, 0.0f } };
qword func_0016A750(struct X *p);
float func_001205C8(qword v);
void func_0011CAE0(M3 *pm, float a, float b);
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Add(qword a, qword b) { qword d; __asm__("vadd.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Len(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(v), "j"(v));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(d) : "j"(d));
    return d;
}
static inline qword Normalize(qword v)
{
    qword l = Len(v), r;
    __asm__("vdiv Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static inline float GFromQ(qword v) { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(v)); return g; }
static inline qword VecMul(qword v, float g)
{
    qword r;
    U s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(g));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s.q));
    return r;
}
static inline qword MulM3(M3 *pm, qword v)
{
    qword r;
    __asm__("vmulax.xyz ACC, %2, %1x\n\tvmadday.xyz ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z" : "=j"(r) : "j"(v), "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]));
    return r;
}
qword func_0016A7E8(struct X *p)
{
    qword r;
    if (p->p14) {
        U n;
        qword a = *(qword *)((char *)p->p14->table[36].get((char *)p->p14 + p->p14->table[36].delta) + 0x30);
        n.q = Normalize(Sub(a, func_0016A750(p)));
        p->gA4 = func_001205C8(n.q);
        r = Add(func_0016A750(p), VecMul(n.q, -GFromQ(Len(s_offset.q))));
    } else {
        M3 m;
        qword v = s_offset.q;
        func_0011CAE0(&m, p->gA4, p->gA8);
        r = Add(func_0016A750(p), MulM3(&m, v));
    }
    return r;
}
