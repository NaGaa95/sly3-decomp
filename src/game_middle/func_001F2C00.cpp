// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Launches `count` objects from an owner's source object towards `target`. The first object is the owner's existing
// one, the others come from its factory. Each launch aims at a random point around the target: a random offset is
// expressed in a basis built from the horizontal part of the start->target direction and the up axis, and
// func_00212628 computes the launch velocity. Class 0x66 objects are launched through func_001F8138 with an
// index-scaled delay; others are reset, parented to the source and given the velocity through virtual calls.
// func_001F2950 cleans up the owner on every exit. Based on Sly 2 func_001C2EF0.
// Sub/Add take their first operand by reference (this decides the stack slot order of target).
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct VTE { short delta, pad; void *fn; };
struct SO { char pad0[0xC]; VTE *vt; char pad10[0x60]; qword position; };
struct OWNER { char pad0[0x194]; SO *source; void *factory; SO *first; };
struct LM { float gMin, gMax; };
extern "C" {
extern qword D_00317550, D_00317530, D_00346FD0;    // up axis, fallback X axis, launch acceleration
extern LM D_00325040, D_00325048, D_00325038;       // random ranges: two offset angles, flight time
extern float D_00325050;
extern char D_003174C0[];
float func_0011E940(float, float);
qword func_0011FD70(float, float, float);
M3 func_0011CBF0(qword, qword);
qword func_00212628(qword, qword, qword, float);
int func_0013B500(SO *, int);
void func_001F8138(SO *, qword, qword, float, float);
SO *func_001FBE30(void *, int);
void func_001F2950(OWNER *);
}

static inline float X(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline qword Sub(const qword &a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(const qword &a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(d), "=&j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword Scale(qword s, qword v) { qword r; __asm__("vmulx.xyzw %0,%2,%1x" : "=j"(r) : "j"(s), "j"(v)); return r; }
static inline qword Length(qword v)
{
    qword d, one, len;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(len) : "j"(d));
    return len;
}
static inline qword Unit(qword v, qword len)
{
    qword r;
    __asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q" : "=j"(r) : "j"(v), "j"(len));
    return r;
}
static inline qword Normalize(qword v, qword fallback)
{
    qword len = Length(v);
    if (X(len) < 0.0001f)
        return fallback;
    return Unit(v, len);
}
static inline qword Transform(const M3 &m, qword q)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(q));
    return r;
}
static inline float Rand(const LM &lm) { return func_0011E940(lm.gMin, lm.gMax); }
static inline void Reset(SO *p) { VTE *v = p->vt; ((void (*)(void *))v[8].fn)((char *)p + v[8].delta); }
static inline void SetParent(SO *p, SO *parent, void *xf) { VTE *v = p->vt; ((void (*)(void *, SO *, void *))v[43].fn)((char *)p + v[43].delta, parent, xf); }
static inline void SetVelocity(SO *p, qword velocity) { VTE *v = p->vt; ((void (*)(void *, qword))v[40].fn)((char *)p + v[40].delta, velocity); }

extern "C" SO *func_001F2C00(OWNER *p, int count, qword target, int fSlow)
{
    SO *first = 0;
    for (int i = 0; i < count; i++) {
        SO *node;
        if (i == 0)
            node = p->first;
        else
            node = func_001FBE30(p->factory, 0);
        if (!node)
            break;
        if (!first)
            first = node;
        qword start = p->source->position;
        float pan = Rand(D_00325040);
        qword offset = func_0011FD70(pan, Rand(D_00325048), -75.0f);
        qword delta = Sub(target, start);
        qword side = Sub(delta, Scale(Dot(delta, D_00317550), D_00317550));
        M3 mat;
        mat = func_0011CBF0(Normalize(side, D_00317530), D_00317550);
        qword dest = Add(target, Transform(mat, offset));
        qword velocity = func_00212628(start, dest, D_00346FD0, Rand(D_00325038));
        if (func_0013B500(node, 0x66)) {
            float lifetime;
            if (fSlow && (func_0013B500(node, 0x67) || func_0013B500(node, 0x69)))
                lifetime = (float)i * 0.15f;
            else
                lifetime = D_00325050;
            func_001F8138(node, p->source->position, velocity, (float)i * 0.05f, lifetime);
        } else {
            Reset(node);
            SetParent(node, p->source, D_003174C0);
            SetVelocity(node, velocity);
        }
    }
    func_001F2950(p);
    return first;
}
