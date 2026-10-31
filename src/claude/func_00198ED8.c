// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct VTE { short d; short pad; unsigned char *(*fn)(void *); };
struct Obj { int pad[3]; struct VTE *vt; };
struct Self { unsigned char pad[0x70]; float f70; int n74; int n78; int n7C; unsigned char pad80[0xA8 - 0x80]; float fA8; };
extern unsigned char D_00475480[];
struct Obj *func_00165B28(void *game);
qword func_001678C8(struct Obj *o, qword target);
int func_00198CF0(qword v, float f);
int func_00165000(int n, qword a, qword b, int c, int d, void *hit);
static inline qword Position(struct Obj *o)
{
    struct VTE *e = &o->vt[36];
    return *(qword *)(e->fn((char *)o + e->d) + 0x30);
}
static inline float GetZ(qword q) { float z; __asm__("pextuw %0,$zero,%1" : "=r"(z) : "r"(q)); return z; }
/* pointer operands: target and pos have their address taken, so they live in stack memory (sq, then lqc2) */
static inline qword VSub(const qword *a, const qword *b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(*a), "j"(*b)); return r; }
static inline float Length(qword v)
{
    qword l, t; float r;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(l), "=&j"(t) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(l));
    __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(l));
    return r;
}
static inline float LengthXY(qword v)
{
    qword l; float r;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(l) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(l));
    __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(l));
    return r;
}
int func_00198ED8(struct Self *self, qword target, int a, int b, float range)
{
    struct Obj *o = func_00165B28(D_00475480);
    U t; qword pos;
    qword d, v;
    float dist;
    pos = Position(o);
    d = VSub(&target, &pos);
    range *= 0.8f;
    { int far = range < Length(d); if (far) return 0; }
    dist = LengthXY(d);
    if (self->fA8 < dist) return 0;
    v = func_001678C8(o, target);
    if (GetZ(v) < 500.0f) return 0;
    if (!func_00198CF0(v, 1.7f)) return 0;
    if (self->n74 && !func_00198CF0(v, 1.25f)) return 1;
    if (self->n78 && self->f70 < dist) return 2;
    if (self->n7C) {
        t.q = target;
        t.f[2] += 100.0f;
        if (func_00165000(0, pos, t.q, a, b, 0)) return 3;
    }
    return 0;
}
