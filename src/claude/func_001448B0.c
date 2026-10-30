// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
extern char *D_00479BD4;
void func_00120BA8(qword v, float *pa, float *pb, float *pc);
float func_0011E3B8(float rad);
void func_002BC350(void *p, int n);
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
static const float s_penalty[2] = { 500.0f, 3000.0f };
void func_001448B0(char *p)
{
    float ang[3];
    float best = 3.402823466e+38f;
    char *pick = 0;
    char *o;
    for (o = D_00479BD4; o; o = *(char **)(o + 0x41C)) {
        qword a, d;
        float e;
        if (*(int *)(o + 0x194) == *(int *)(p + 0x194))
            continue;
        a = matrix_of((struct Object *)o)->rows[3];
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(matrix_of((struct Object *)p)->rows[3]));
        func_00120BA8(d, &ang[1], 0, &ang[2]);
        e = __builtin_fabsf(func_0011E3B8(ang[1] - *(float *)(p + 0x1E8)));
        if (*(float *)(p + 0x1B8) < e) {
            float t = (e - *(float *)(p + 0x1B8)) / (3.1415927f - *(float *)(p + 0x1B8));
            const float *k = s_penalty;
            ang[2] += (1.0f - t) * k[0] + t * k[1];
        }
        if (o == *(char **)(p + 0x3B8))
            ang[2] += -1000.0f;
        if (!*(int *)(o + 0x198))
            ang[2] += -750.0f;
        if (ang[2] < best) {
            best = ang[2];
            pick = o;
        }
    }
    *(char **)(p + 0x3B8) = pick;
    func_002BC350(ang, 2);
}
