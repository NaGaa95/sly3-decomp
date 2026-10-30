// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; void *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
struct CLOCK { float t; };
extern struct CLOCK g_clock;
void func_0028F680(void *a, void *b, float *m, float *n, float f);
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return (struct Matrix *)method->call((unsigned char *)object + method->delta);
}
static inline float Length(qword v)
{
    qword d, one, l;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
    return g;
}
int func_00154DA0(char *p)
{
    qword spare[3];
    struct { qword pos; float m[16]; } x;
    qword w, d;
    struct Object *o;
    if (*(int *)(p + 0x508) != 5)
        return 1;
    if (!*(int *)(p + 0x514))
        return 1;
    o = *(struct Object **)(p + 0x974);
    func_0028F680(((void *(*)(void *, void *))o->methods[37].call)((char *)o + o->methods[37].delta, spare), 0, x.m, 0, 0.0f);
    {
    qword pt = x.pos;
    __asm__("vmulax.xyz $ACC, %1, %2x\n\tvmadday.xyz $ACC, %3, %2y\n\tvmaddaz.xyz $ACC, %4, %2z\n\tvmaddw.xyz %0, %5, $vf0w"
            : "=j"(w) : "j"(((qword *)x.m)[0]), "j"(pt), "j"(((qword *)x.m)[1]), "j"(((qword *)x.m)[2]), "j"(((qword *)x.m)[3]));
    }
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(matrix_of(*(struct Object **)(p + 0x974))->rows[3]), "j"(w));
    if (Length(d) > 5.0f)
        return 0;
    if (*(int *)(p + 0x9E4) != 1)
        return 1;
    if (g_clock.t < *(float *)(*(char **)(p + 0x9D4) + 0x1C))
        return 0;
    return 1;
}
