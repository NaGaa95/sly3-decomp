// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; unsigned char pad10[0x10C - 0x10]; int mask; int pad110; float w; };
struct V4 { float x, y, z, w; } __attribute__((aligned(16)));
struct Self { char pad[0x3EB8]; int count; struct Object *objects[1]; };
int func_00168DD8(struct Object *o);
void func_00166A40(struct Object *o);
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
int func_0015AF58(struct Self *self, int *pmask, struct V4 *out)
{
    int i, n = 0, mask = 0;
    for (i = 0; i < self->count; i++) {
        struct Object *o = self->objects[i];
        if (func_00168DD8(o))
            continue;
        func_00166A40(o);
        n++;
        mask |= o->mask;
        {
            struct V4 *pv = &(out - 1)[n];
            qword pos = matrix_of(o)->rows[3];
            float w = o->w;
            *(qword *)pv = pos;
            pv->w = w;
        }
    }
    if (!n) {
        out->w = 0.0f;
        out->z = 0.0f;
        out->y = 0.0f;
        out->x = 0.0f;
        n = 1;
        mask = 0xFF;
    }
    *pmask = mask;
    return n;
}
