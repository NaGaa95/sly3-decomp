// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Picks the closest flagged object in front of the actor (between 150 and 1.3 * the actor's reach, almost level, and
// within about one radian of the actor's heading) and stores it as the actor's selection. Sly 2 relative: func_001B5E98.
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Frame { float row0[4]; };
struct Node {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0xD0 - 0x10];
    struct Node *next;
    unsigned char gapD4[4];
    unsigned flags;
};
struct Actor {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x1540 - 0x10];
    void *context;
    unsigned char gap1544[0x1560 - 0x1544];
    float reach;
    unsigned char gap1564[4];
    struct Node *selected;
};
struct Scope { unsigned char storage[16]; };
extern struct { struct Node *first; } D_00479AD8;
int func_001A22F8(void *context, struct Node *node);
float func_001205C8(qword v);
float func_002A3EE8(float y, float x);
float func_0011E3B8(float angle);
void func_002BC490(void *p, int n);
static inline struct Frame *Matrix(void *object)
{
    struct Method *method = &((struct Node *)object)->methods[36];
    return ((struct Frame *(*)(void *))method->function)((char *)object + method->adjustment);
}
static inline qword Position(void *object)
{
    return ((qword *)Matrix(object))[3];
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float PlanarLength(qword v)
{
    qword d;
    float g;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0,%1" : "=r"(g) : "j"(d));
    return g;
}
static inline float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
void func_001DE4D8(struct Actor *self)
{
    struct Scope scope;
    struct Node *node;
    float best;
    self->selected = 0;
    best = self->reach * 1.3f;
    for (node = D_00479AD8.first; node; node = node->next) {
        qword d;
        float length, heading;
        struct Frame *facing;
        if (!(node->flags & 0x10000))
            continue;
        if (func_001A22F8(self->context, node))
            continue;
        d = Sub(Position(node), Position(self));
        length = PlanarLength(d);
        if (best < length)
            continue;
        if (length < 150.0f)
            continue;
        if (500.0f < __builtin_fabsf(GetZ(d)))
            continue;
        heading = func_001205C8(d);
        facing = Matrix(self);
        if (1.0f < __builtin_fabsf(func_0011E3B8(heading - func_002A3EE8(facing->row0[1], facing->row0[0]))))
            continue;
        self->selected = node;
        best = length;
    }
    func_002BC490(&scope, 2);
}
