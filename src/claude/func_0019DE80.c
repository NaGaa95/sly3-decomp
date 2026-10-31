// SLY3_CFLAGS: -Os -fno-sched-interblock -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
typedef struct VirtualEntry { short adjustment; short reserved; M4 *(*call)(); } VirtualEntry;
struct Obj { unsigned char opaque0[12]; VirtualEntry *vtable; };
struct Self {
    unsigned char opaque0[12]; VirtualEntry *vtable;
    unsigned char pad10[0x1F0 - 0x10]; int state; int pad1F4; struct Obj *found; struct Obj *anchor;
};
extern unsigned char D_00475480[];
void func_0023C660(struct Self *self);
int func_0017E208(void *world, int kind, int flags, int a, int max, struct Obj **out);
void func_0019E060(struct Self *self, int state);
int func_0019BAA0(struct Self *self);
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
void func_0019DE80(struct Self *self)
{
    int state;
    func_0023C660(self);
    do {
        state = self->state;
        switch (state) {
        case 0: {
            struct Obj *list[4];
            int count = func_0017E208(D_00475480, 0x105, 0x4A, 0, 4, list);
            int i;
            for (i = 0; i < count; i++) {
                struct Obj *obj;
                obj = list[i];
                {
                qword pos = Matrix(obj)->r[3];
                qword d = Sub(pos, Matrix(self->anchor)->r[3]);
                if (GetX(SqrtX(Dot3(d, d))) < 50.0f) {
                    self->found = obj;
                    func_0019E060(self, 1);
                }
                }
            }
            break;
        }
        case 1:
            if (func_0019BAA0(self)) func_0019E060(self, 2);
            break;
        }
    } while (self->state != state);
}
