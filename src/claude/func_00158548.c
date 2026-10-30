// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
struct Self { char pad[0x10]; char *actor; char pad14[0x30 - 0x14]; struct Object *target; char pad34[0x90 - 0x34]; qword pos; };
char *func_00158648(struct Self *self);
int func_0013B500(void *object, int kind);
int func_001ED1F0(void *t, qword pos, int n);
int func_00198D78(qword *pos, int a, int b, float g0, float g1);
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
int func_00158548(struct Self *self)
{
    char *t = func_00158648(self);
    char *a, *b, *c;
    qword pos;
    if (!t)
        return 0;
    a = *(char **)(self->actor + 0xD8);
    b = a ? *(char **)(a + 0xDC) : 0;
    c = b ? *(char **)(b + 0x10) : 0;
    if (t == c)
        return 0;
    if (*(int *)(t + 0x18) == 0x321)
        return 0;
    if (func_0013B500(self->target, 0x33) && *(int *)((char *)self->target + 0x33C) != -1)
        return 0;
    pos = matrix_of(self->target)->rows[3];
    if (!func_001ED1F0(t, pos, 0))
        return 0;
    if (!func_00198D78(&pos, 0, 0, 100.0f, -350.0f))
        return 0;
    self->pos = pos;
    return 1;
}
