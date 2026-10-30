// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
struct Q { char pad[0x14]; void *other; char pad18[0x40 - 0x18]; qword v; int flags; };
extern qword D_00317550;
int func_0013B500(void *object, int kind);
void func_0014C9B8(void *p, qword pos, qword dir, void *other);
void func_0014CB98(void *p, float g);
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
static inline qword Len(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword Div(qword v, qword l)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static __inline__ float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline void Normalize(qword *pn, qword v)
{
    qword l, fb;
    register qword n __asm__("vf1"); /* register pin: normalized direction lives in vf1 on both paths */
    l = Len(v);
    fb = D_00317550;
    if (F(l) < 1.0e-4f)
        n = fb;
    else
        n = Div(v, l);
    *pn = n;
}
int func_0014C890(char *p, struct Q *q)
{
    if (*(int *)(p + 0x130) != 1 && (q->flags & 2)) {
        union { qword q; float f[4]; } u;
        Normalize(&u.q, q->v);
        func_0014C9B8(p, matrix_of((struct Object *)p)->rows[3], u.q, q->other);
        if (func_0013B500(q->other, 0x59))
            func_0014CB98(p, 0.25f);
        else
            func_0014CB98(p, 0.0f);
        return 1;
    }
    return 0;
}
