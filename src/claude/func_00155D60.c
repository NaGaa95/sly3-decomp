// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; void *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
struct Result { int kind; float g4; float g8; int pad; qword pos; qword dir; };
extern qword D_00317550;
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return (struct Matrix *)method->call((unsigned char *)object + method->delta);
}
static inline qword velocity_of(struct Object *object)
{
    struct Method *method = &object->methods[38];
    return ((qword (*)(void *))method->call)((unsigned char *)object + method->delta);
}
static inline qword splat(float g)
{
    U u;
    __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(g));
    return u.q;
}
void func_00155D60(struct Object *o, struct Result *r, float g)
{
    qword v = velocity_of(o);
    qword d, one, t, h, pos;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(v), "j"(D_00317550));
    __asm__("vmulx.xyzw %0, %1, %0x" : "=j"(t) : "j"(D_00317550), "0"(d));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(h) : "j"(v), "j"(t));
    {
        struct Matrix *m = matrix_of(o);
        __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(pos) : "j"(m->rows[3]), "j"(h), "j"(splat(g)));
    }
    r->g4 = 150.0f;
    r->g8 = 75.0f;
    r->pos = pos;
    r->kind = 0;
    r->dir = h;
}
