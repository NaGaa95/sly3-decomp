// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
struct Self { char pad[0x10]; char *actor; char pad14[4]; void *sound; char pad1C[0x30 - 0x1C]; int mode; char pad34[0x40 - 0x34]; qword pos; };
char *func_001ED678(qword pos, int n);
int func_00198D78(qword *pos, int a, int b, float g0, float g1);
void *func_001EF038(qword a, qword b, void *c);
void func_001D8B40(void *a, void *b);
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
void func_00157970(struct Self *self, qword pos)
{
    char *actor, *a, *b, *c;
    self->pos = pos;
    if (!self->sound)
        return;
    actor = self->actor;
    a = *(char **)(actor + 0xD8);
    b = a ? *(char **)(a + 0xDC) : 0;
    c = b ? *(char **)(b + 0x10) : 0;
    if (!self->mode && func_001ED678(pos, 1) != c) {
        qword v = pos;
        struct Object *o;
        qword d;
        func_00198D78(&v, 0, 0, 100.0f, -350.0f);
        o = (struct Object *)self->actor;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(v), "j"(*(qword *)((char *)o + 0x260)));
        ((void (*)(void *, qword))o->methods[34].call)((char *)o + o->methods[34].delta, d);
    }
    func_001D8B40(self->sound, func_001EF038(matrix_of((struct Object *)actor)->rows[3], self->pos, self->mode ? 0 : c));
}
