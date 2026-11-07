// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00277830 (agents A60/A73): line-segment hit -> record the hit and push the struck body (cf. Sly 2 func_00224820).
// The first dot product reads its lane with an mtc1 lane asm (gcc emits the qmfc2 itself, which delays the mtc1 one cycle
// and fixes the D_00341FF0/s_poly load order); one pin keeps that dot's accumulator in vf1.
typedef int qword __attribute__((mode(TI)));
struct O;
struct VE { short delta, pad; union { qword (*get)(void *); void (*set)(void *, qword); } f; };
struct NODE { char pad[0x70]; qword position; };
struct STATE { char pad[0x60]; O *owner; };
struct CHAIN { char pad[0xDC]; STATE *state; };
struct O { char pad[0xC]; VE *vt; char pad10[0x3C]; NODE *rotation; NODE *motion; char pad54[0xD8 - 0x54]; void *physics; };
struct COLL { void *source; CHAIN *object; };
struct LSG { qword point; char remainder[0x50]; };
struct HIT { char pad[0x1C]; CHAIN *object; };
struct POLY { float a, b, c; };
struct RANGE { float lo, hi; };
extern RANGE D_00341FF0;
static const POLY s_poly = { 1.0f, 0.0f, -1.0f };
extern "C" {
COLL *func_00165000(int, qword, qword, int, COLL **, LSG *);
void func_00240CB0(O *, int, CHAIN *, int, int, int, qword, qword, HIT **);
qword func_0028BCD0(NODE *, NODE *, qword);
qword func_002445E8(O *, qword);
qword func_00244630(O *, qword, qword);
}
struct VV { qword q; VV(qword v) { q = v; } };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_FLOATM { qword q; VU_FLOATM(float f) { __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); } };
static inline qword Sub(const qword &a, const qword &b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Diff(const qword &b, const qword &a) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(const qword &a, const qword &b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Cross(const qword &a, qword b) { __asm__("vopmula.xyz $ACC, %1, %0\n\tvopmsub.xyz %0, %0, %1" : "+j"(b) : "j"(a)); return b; }
static inline float Dot(const qword &a, const qword &b)
{
    qword qw, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=j"(one) : "j"(a), "j"(b));
    float x;
    __asm__("qmfc2.ni %0, %1" : "=r"(x) : "j"(qw));
    return x;
}
static inline float DotM(const qword &a, const qword &b)
{
    register qword qw asm("vf1"); qword one; // pin
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=j"(one) : "j"(a), "j"(b));
    float x;
    __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw));
    return x;
}
static inline qword Normalize(const qword &v)
{
    qword len, one, r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(len), "=&j"(one) : "j"(v), "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(len) : "j"(len));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(len), "j"(v));
    return r;
}
static inline qword operator*(const qword &v, VU_FLOAT k) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(k.q)); return r; }
static inline qword AddScaled(qword old, const qword &v, VU_FLOATM k) { __asm__("vadda.xyzw $ACC, %0, $vf0\n\tvmaddx.xyzw %0, %2, %1x" : "+j"(old) : "j"(k.q), "j"(v)); return old; }
static inline float Clamp(float f, float lo, float hi) { float r; if (f < lo) r = lo; else if (hi < f) r = hi; else r = f; return r; }
static inline qword Get(O *o, int slot) { VE *v = o->vt; return v[slot].f.get((char *)o + v[slot].delta); }
static inline void Set(O *o, int slot, qword q) { VE *v = o->vt; v[slot].f.set((char *)o + v[slot].delta, q); }
extern "C" void func_00277830(O *owner, int filter, int channel, int x, qword start, qword end, int queryCount, COLL **objects,
                              int capacity, int *count, HIT **records)
{
    LSG hit;
    COLL *collider = func_00165000(0, start, end, queryCount, objects, &hit);
    if (!collider) return;
    qword normal = Normalize(Diff(start, end));
    CHAIN *chain = collider->object;
    O *body = chain->state->owner;
    int i;
    for (i = 0; i < *count; i++)
        if (records[i]->object == chain) break;
    if (i >= *count && *count < capacity) {
        HIT *record;
        func_00240CB0(owner, 0, chain, filter, channel, x, hit.point, normal * VU_FLOAT(1000.0f), &record);
        records[(*count)++] = record;
    }
    if (!body->physics) return;
    float along = DotM(func_0028BCD0(body->motion, 0, hit.point), normal);
    float ratio = along * 0.001f;
    float response = Clamp(s_poly.a + ratio * (s_poly.b + ratio * s_poly.c), D_00341FF0.lo, D_00341FF0.hi);
    float fz = 0.0f;
    if (fz < response) {
        qword impulse = normal * VU_FLOAT(response * 100.0f);
        VV linear(func_002445E8(body, impulse));
        VV angular(func_00244630(body, hit.point, impulse));
        qword delta = Sub(hit.point, body->rotation->position);
        float change = Dot(Add(linear.q, Cross(angular.q, delta)), normal);
        if (fz < change) {
            float t = (1000.0f - along) / change;
            float one = 1.0f;
            if (t < fz) {} else if (one < t) fz = one; else fz = t;
            qword velocity = AddScaled(Get(body, 38), linear.q, VU_FLOATM(fz));
            qword spin = AddScaled(Get(body, 39), angular.q, VU_FLOATM(fz));
            Set(body, 40, velocity);
            Set(body, 41, spin);
        }
    }
}
