// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; unsigned char pad10[0x2C - 0x10]; unsigned char mask; };
struct Slot { char pad[0x11C0]; };
union V4 { qword q; struct { int x, y, z; float w; } s; };
extern struct Slot D_0036E740[];
struct Object *func_001F4B30(struct Slot *slot);
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
int func_0015B820(void *self, union V4 *out, int *pmask)
{
    int i, n = 0, mask = 0;
    union V4 *pv = out - 1;
    for (i = 0; i < 2; i++) {
        struct Object *o = func_001F4B30(&D_0036E740[i]);
        if (!o)
            continue;
        pv++;
        n++;
        pv->q = matrix_of(o)->rows[3];
        pv->s.w = 1.0f;
        mask |= o->mask;
    }
    if (!n) {
        *(int *)&out->s.w = 0;
        out->s.z = 0;
        out->s.y = 0;
        out->s.x = 0;
        n = 1;
        mask = 0xFF;
    }
    *pmask = mask;
    return n;
}
