// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Refresh the contact data of a shape attached to `self`: for a kind 8 shape on side 0 it copies the source axis, makes sure the
// body's point set is current and stores the lowest signed distance of the points along that axis. It then derives the facing
// normal (axis, or negated for the other side) and sets the two slide factors depending on whether the normal is steep enough
// and on how it lines up with the third row of the owner's matrix.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct VTE { short delta; short pad; qword *(*method)(void *); };
struct VOBJ { unsigned char pad0[0xC]; VTE *vt; };
struct BodyClass { unsigned char pad[0xA4]; int stamp; };
struct Points { int pad0; qword *data; };
struct Body {
    BodyClass *cls;
    unsigned char pad04[0x1C];
    int count;
    unsigned char pad24[0x7C];
    Points points;
    unsigned char padA8[0x18];
    int stamp;
};
struct Side { int pad0; int pad4; void *target; unsigned char pad0C[0x34]; };
struct Shape {
    Body *body;
    unsigned char pad04[0x4C];
    qword position;
    unsigned char pad60[0x20];
    qword axis;
    float depth;
    float rise;
    float fall;
    int kind;
    qword *source;
};
extern "C" {
void func_0023E110(VOBJ *self, Shape *shape, int side);
void func_0018B1E0(Body *body);
int func_0013B500(void *target, int kind);
}
static inline qword Broadcast(float f)
{
    qword q;
    __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f));
    return q;
}
static inline qword Scale(qword a, qword s)
{
    qword r;
    // the second "j"(s) is allocation-only (VU numbering of the operands)
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s), "j"(s));
    return r;
}
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword DotA(qword a, qword b)
{
    qword d, t;
    // the second "j"(b) is allocation-only (VU numbering of the operands)
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(d), "=j"(t) : "j"(a), "j"(b), "j"(b));
    return d;
}
static inline qword DotB(qword b, qword a)
{
    qword d, t;
    __asm__("vmul.xyz %0, %3, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(d), "=j"(t) : "j"(b), "j"(a));
    return d;
}
static inline float F3(qword q)
{
    float g;
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q), "j"(q));
    return g;
}
static inline float GetZ(qword q)
{
    float z;
    __asm__("pextuw %0, $0, %0" : "=r"(z) : "0"(q));
    return z;
}
extern "C" void func_00206D40(VOBJ *self, Shape *shape, int side)
{
    U scale;
    qword normal;
    func_0023E110(self, shape, side);
    if (shape->kind == 8 && side == 0) {
        Body *body = shape->body;
        shape->axis = *shape->source;
        if (body->stamp != body->cls->stamp)
            func_0018B1E0(body);
        int count = body->count;
        Points *points = &body->points;
        qword position = shape->position;
        float lowest = 0.0f;
        for (int i = 0; i < count; i++) {
            float d = F3(DotA(Sub(points->data[i], position), shape->axis));
            if (d < lowest) lowest = d;
        }
        shape->depth = lowest;
    }
    if (side == 0) normal = shape->axis;
    else {
        scale.q = Broadcast(-1.0f);
        normal = Scale(shape->axis, scale.q);
    }
    float limit = 0.7f;
    if (GetZ(normal) < limit || func_0013B500(((Side *)((char *)shape + ((1 - side) << 6)))->target, 0x55)) {
        shape->rise = 0.0f;
        shape->fall = 0.1f;
    } else {
        VTE *entry = &self->vt[36];
        qword *rows = entry->method((char *)self + entry->delta);
        if (limit < F3(DotB(rows[2], normal))) {
            shape->rise = 0.1f;
            shape->fall = 0.1f;
        } else {
            shape->rise = 0.5f;
            shape->fall = 0.1f;
        }
    }
}
