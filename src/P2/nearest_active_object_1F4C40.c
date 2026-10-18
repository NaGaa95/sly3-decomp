// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword row[4]; };
struct Method { short delta, reserved; struct Matrix *(*function)(void *); };
struct Object { unsigned char prefix[0xC]; struct Method *table; unsigned char gap10[0x18]; unsigned long flags; };
struct World { unsigned char prefix[0x45E8]; int count; struct Object *objects[1]; };
extern float D_003250A0;
static inline qword Sub(qword a,qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a),"j"(b)); return r; }
static inline float LenSq(qword a) {
    qword d,one; float f;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d),"=&j"(one) : "j"(a));
    __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(d));
    return f;
}

struct Object *func_001F4C40(struct World *world, qword point)
{
    struct Object *best = 0;
    int i = 0;
    float minimum = D_003250A0;
    for (; i < world->count; ++i) {
        struct Object *object = world->objects[i];
        if ((int)(object->flags >> 56) & 1) {
            struct Method *method = &object->table[36];
            struct Matrix *matrix = method->function((char *)object + method->delta);
            float distance = LenSq(Sub(point, matrix->row[3]));
            if (distance < minimum) {
                minimum = distance;
                best = object;
            }
        }
    }
    return best;
}
