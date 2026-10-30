// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
typedef struct VirtualEntry { short adjustment; short reserved; M4 *(*call)(); } VirtualEntry;
struct Obj {
    unsigned char opaque0[12]; VirtualEntry *vtable;
    unsigned char pad10[0x1C8 - 0x10]; struct Obj *favored; int pad1CC; int team;
};
extern unsigned char D_00475480[];
int func_0017E208(void *world, int kind, int flags, int a, int max, struct Obj **out);
static inline M4 *Matrix(struct Obj *object)
{
    VirtualEntry *entry = &object->vtable[36];
    return ((M4 *(*)(void *))entry->call)((char *)object + entry->adjustment);
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Dot3(qword a, qword b)
{
    qword product, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
        : "=j"(product), "=&j"(one) : "j"(a), "j"(b));
    return product;
}
static inline qword SqrtX(qword value)
{
    qword root;
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(root) : "j"(value));
    return root;
}
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
struct Obj *func_0019BC68(struct Obj *self)
{
    struct Obj *list[128];
    float best = 3.402823466e+38f;
    struct Obj *nearest = 0;
    int count = func_0017E208(D_00475480, 0x105, 0x4A, 0, 0x80, list);
    int i;
    for (i = 0; i < count; i++) {
        struct Obj *obj = list[i];
        qword pos, d;
        float dist;
        if (obj->team == self->team) continue;
        pos = Matrix(obj)->r[3];
        d = Sub(pos, Matrix(self)->r[3]);
        dist = GetX(SqrtX(Dot3(d, d)));
        if (obj == self->favored) dist -= 500.0f;
        if (dist < best) {
            best = dist;
            nearest = obj;
        }
    }
    return nearest;
}
