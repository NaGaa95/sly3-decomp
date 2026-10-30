// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
struct Self { char pad[0x10]; char *actor; char pad14[0x30 - 0x14]; int state; int pad34; struct Object *target; int pending; };
void func_001A9960(void *p, float g);
float func_001205C8(qword v);
void func_001A9940(void *p, int n);
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
void func_00158C00(struct Self *self)
{
    qword a, d;
    { int s = self->state; if (s >= 3) return; if (s < 0) return; }
    a = matrix_of(self->target)->rows[3];
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(matrix_of((struct Object *)self->actor)->rows[3]));
    func_001A9960(self->actor + 0x140C, self->state == 0 ? 0.1f : 1.0f);
    *(float *)(self->actor + 0x110C) = func_001205C8(d);
    if (self->state == 2 && self->pending) {
        func_001A9940(self->actor + 0x140C, 0x80);
        self->pending = 0;
    }
}
