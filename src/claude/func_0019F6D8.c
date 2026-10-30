// SLY3_ASFIX: engine-divfix1
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Planar() is the Sly 2 helper from func_001823C8 (normalize xy direction with a zero fallback).
typedef int qword __attribute__((mode(TI)));
typedef union U { qword q; float f[4]; int i[4]; } U;
struct VTE { short d; short pad; unsigned char *(*fn)(void *); };
struct Obj {
    int pad[3]; struct VTE *vt; unsigned char pad10[0x1D0 - 0x10];
    int group; float weight; float nearDist; float farDist; float strength; struct Obj *next;
};
/* Object lists of 0x18 bytes each; the third one starts at 0x00479D8C. */
struct List { struct Obj *head; int pad[5]; };
extern struct List D_00479D5C[];
extern qword D_00317560;
extern unsigned char D_00341FF0[];
float func_0011EE68(void *curve, float u);
qword func_001205F0(qword v, float max);
void func_00244828(struct Obj *self, qword v);
static inline qword Position(struct Obj *o)
{
    struct VTE *e = &o->vt[36];
    return *(qword *)(e->fn((char *)o + e->d) + 0x30);
}
static inline qword Sub(qword a, qword b) { __asm__("vsub.xyzw %0,%0,%1" : "+j"(a) : "j"(b)); return a; }
static inline qword Broadcast(float f) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(f)); return r; }
static inline float Scalar(qword a) { float f; __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(a)); return f; }
static inline qword MAdd(qword a, qword b, qword s) { __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x" : "+j"(a) : "j"(b), "j"(s)); return a; }
static inline float GX(qword qw) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(qw)); return x; }
static inline float Planar(U *p)
{
    const qword *zero = &D_00317560;
    qword direction = p->q;
    qword d, root;
    qword dv;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(d), "=&j"(root), "=j"(dv) : "2"(direction), "r"(direction), "r"(direction));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(root) : "j"(d));
    if (Scalar(root) < 0.0001f) p->q = *zero;
    else { __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(d) : "j"(dv), "j"(root)); p->q = d; }
    return GX(root);
}
void func_0019F6D8(struct Obj *self)
{
    U acc, dir, scale;
    qword pos;
    struct Obj *o;
    if (self->strength <= 0.0f) return;
    pos = Position(self);
    acc.f[2] = 0.0f;
    acc.f[1] = 0.0f;
    acc.f[0] = 0.0f;
    for (o = D_00479D5C[2].head; o; o = o->next) {
        float dist, u, w;
        void *curve;
        if (o->group == self->group) continue;
        dir.q = Sub(Position(o), pos);
        dir.i[2] = 0;
        dist = Planar(&dir);
        curve = D_00341FF0;
        if (o->nearDist == o->farDist) u = 0.0f;
        else u = (dist - o->nearDist) / (o->farDist - o->nearDist);
        w = func_0011EE68(curve, 1.0f - u);
        scale.q = Broadcast(self->strength * o->weight * w);
        acc.q = MAdd(acc.q, dir.q, scale.q);
    }
    acc.q = func_001205F0(acc.q, 4500.0f);
    func_00244828(self, acc.q);
}
