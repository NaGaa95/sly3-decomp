// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
qword func_0011FD70(float radPan, float radTilt, float r);
qword func_001407E8(void *self);
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
int func_00140BF0(char *p)
{
    char *o = *(char **)(p + 0x10);
    qword dir, d, pos;
    if (!(0.0f < *(float *)(*(char **)(o + 0x134) + 8)))
        return *(int *)(p + 0x1C);
    dir = func_0011FD70(*(float *)(o + 0x110C) - 1.5707964f, 1.0f, 0.0f);
    pos = func_001407E8(p);
    {
        qword base = matrix_of(*(struct Object **)(p + 0x10))->rows[3];
        qword one;
        float g;
        int r = 0;
        qword dd;
        __asm__("vsub.xyzw %0, %0, %1" : "=j"(d) : "j"(base), "0"(pos));
        __asm__("vmul.xyz %0, %2, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
                : "=j"(dd), "=j"(one) : "j"(dir), "0"(d), "1"(base));
        __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(dd));
        if (!(0.0f < g))
            r = 1;
        return r;
    }
}
