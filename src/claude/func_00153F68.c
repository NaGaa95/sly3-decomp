// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
int func_0013B500(void *object, int kind);
void func_001ADDD0(void *p, int a, int b);
qword func_00212480(qword pos, qword a, qword b, float g);
void func_001B7268(void *context, int kind, void *resource, void *record, float gain);
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
void func_00153F68(char *p, qword a, float g, float limit)
{
    union { qword q; float f[4]; } pos;
    union { qword q; float f[4]; } r;
    pos.q = matrix_of((struct Object *)p)->rows[3];
    pos.f[2] += *(float *)(p + 0x268);
    if (func_0013B500(p, 0x34) && *(int *)(p + 0x19E0) == 0x13)
        func_001ADDD0(p, 0, -1);
    r.q = func_00212480(pos.q, a, *(qword *)(*(char **)(p + 0xD8) + 0x80), g);
    {
        struct Object *o = (struct Object *)p;
        ((void (*)(void *, qword))o->methods[40].call)((char *)o + o->methods[40].delta, r.q);
    }
    if (*(int *)(p + 0xE44) != -1)
        return;
    {
    char *c = p + 0x320;
    func_001B7268(c, 8, 0, 0, 1.0f);
    *(int *)(p + 0x35C) = 3;
    *(qword *)(p + 0x370) = r.q;
    *(int *)(p + 0x378) = 0;
    *(float *)(p + 0x350) = limit;
    if (limit == *(float *)(p + 0x378))
        *(int *)(c + 0x28) = *(int *)(c + 0x190);
    }
}
