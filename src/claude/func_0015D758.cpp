// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions
// func_0015D758 (agent A43, from A18 r5n.cpp).
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
static inline float PackedVectorZ(qword vector) {
    float scalar;
    __asm__("pextuw %0,$0,%1" : "=r"(scalar) : "r"(vector));
    return scalar;
}
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
static inline bool FBelow(qword a, qword b)
{
    return PackedVectorZ(a) < PackedVectorZ(b);
}
extern "C" int func_0015C9A8(void *self, void *item, qword a, qword b, struct Object *o);

extern "C" int func_0015D758(void *self, void *item, qword pos, qword normal, struct Object *o)
{
    if (!func_0015C9A8(self, item, pos, normal, o))
        return 0;
    if (!(PackedVectorZ(normal) < 0.7f)) {
        if (FBelow(matrix_of(o)->rows[3], pos))
            return 0;
        __asm__ __volatile__(""); /* zero-insn: blocks jump.c conditional-move of the 0/1 return (target keeps bnez + li) */
        return 1;
    }
    return 0;
}
