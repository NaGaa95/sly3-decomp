// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Consumes the pending link of the actor: when the linked object is flagged, it is re-placed at the actor position (plus an
// offset from heading/radius, replaced by the transformed position of the second object when present) and gets state 2.
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct M4 { qword r[4]; };
struct Object {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x28 - 0x10];
    unsigned long flags;
};
struct Link { unsigned char prefix[0x190]; Object *object; };
struct Actor {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x1BC - 0x10];
    float g1BC;
    unsigned char gap1C0[0x1540 - 0x1C0];
    Link *link;
    unsigned char gap1544[0x1560 - 0x1544];
    float g1560;
    float g1564;
    Object *p1568;
};
extern "C" {
void func_001E0660(Actor *self);
int func_0013B500(void *object, int key);
void func_00255A40(void *object);
qword func_0011FD70(float a, float b, float c);
void func_0028F680(void *p, int a, void *pv, float g, int b);
void func_0011D558(M4 *out, M4 *a, M4 *b);
qword func_0023ED38(void *object);
qword func_00212628(qword a, qword b, qword c, float g);
void func_00241150(void *object, int n);
}
static inline qword Position(void *self)
{
    struct Method *method = &((struct Object *)self)->methods[36];
    return ((M4 *(*)(void *))method->function)((char *)self + method->adjustment)->r[3];
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float PlanarLength(qword v)
{
    qword d, l;
    float g;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    __asm__("mtc1 %1,%0" : "=f"(g) : "r"(l));
    return g;
}
extern "C" void func_001E0160(Actor *self)
{
    func_001E0660(self);
    Object *o = self->link->object;
    self->link = 0;
    int flagged = (o->flags & (1UL << 56)) != 0;
    if (flagged) {
        if (func_0013B500(o, 0x3A))
            func_00255A40(o);
        qword v = Add(Position(self), func_0011FD70(self->g1BC, self->g1560, 0.0f));
        if (self->p1568) {
            M4 m0, m1, m2;
            struct Method *method = &self->p1568->methods[37];
            void *s1 = ((void *(*)(void *, M4 *))method->function)((char *)self->p1568 + method->adjustment, &m0);
            float reach = PlanarLength(Sub(Position(o), Position(self->p1568))) / self->g1564;
            func_0028F680(s1, 0, &m1, reach, 0);
            func_0011D558(&m2, &m1, &m0);
            v = m2.r[3];
        }
        float g = PlanarLength(Sub(Position(o), v)) / self->g1564;
        qword pos = Position(o);
        qword r = func_00212628(pos, v, func_0023ED38(o), g);
        struct Method *set = &o->methods[40];
        ((void (*)(void *, qword))set->function)((char *)o + set->adjustment, r);
        func_00241150(o, 2);
    }
}
