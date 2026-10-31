// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Count the objects in the owner's list whose position lies within a radius of a point.
// The local scope object has no constructor; its destructor is the shared out-of-line release hook func_002BEB30.
typedef int qword __attribute__((mode(TI)));
extern "C" void func_002BEB30(void *object, int flags);
struct ReleaseScope {
    qword storage;
    ~ReleaseScope() { func_002BEB30(this, 2); }
};
struct Node {
    char pad0[8];
    Node *next;
    char pad0C[0x70 - 0xC];
    qword position;
};
struct Owner {
    char pad[0x50];
    Node *first;
};
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Dot(qword a, qword b)
{
    qword d = a, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "0"(d), "j"(b));
    return d;
}
static inline float XOf(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
// A float carried as raw bits in a general register.
struct GprFloat {
    qword q;
    GprFloat(float g) { __asm__("mfc1 %0,%1" : "=r"(q) : "f"(g)); }
};
extern "C" int func_00202958(Owner *self, qword point, float radius)
{
    int count = 0;
    GprFloat limit(radius * radius);
    ReleaseScope scope;
    for (Node *node = self->first; node; node = node->next) {
        qword d = Sub(point, node->position);
        if (XOf(Dot(d, d)) <= XOf(limit.q))
            count++;
    }
    return count;
}
