// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
void func_00120BA8(qword v, float *pa, float *pb, int n);
float func_0011E3B8(float rad);
float func_0011E560(float g, float limit);
void func_00144E40(void *p);
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
void func_00144580(char *p)
{
    float ang[2];
    qword target = *(qword *)(p + 0x3A0);
    qword d;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(target), "j"(matrix_of((struct Object *)p)->rows[3]));
    func_00120BA8(d, &ang[0], &ang[1], 0);
    *(float *)(p + 0x408) = func_0011E560(func_0011E3B8(-ang[1]), *(float *)(p + 0x1AC));
    *(float *)(p + 0x40C) = func_0011E3B8(ang[0]);
    *(float *)(p + 0x404) = func_0011E560(func_0011E3B8(*(float *)(p + 0x1E8) - *(float *)(p + 0x40C)), *(float *)(p + 0x1B0));
    func_00144E40(p);
}
