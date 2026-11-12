// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Spawns one particle per entry of a launch batch: each is allocated from the emitter pool, started through its first virtual hook with the
// batch position and a random value from the program range, takes the batch velocity/range, the emitter shape (origin, normalised axis, spin),
// the owner's matrix and is finished through its second hook.
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct Matrix { qword r0, r1, r2; };
struct Frame { char pad0[0xC]; VTE *vt; };
struct Owner { char pad0[0x14]; Frame *frame; char pad18[0x20 - 0x18]; Matrix local; };
struct Program { char pad0[0x14]; float rangeMin, rangeMax; int id; };
struct Shape {
    qword origin; qword axis; char pad20[4]; float s24, s28; char pad2C[4]; qword v30;
    char pad40[0x68 - 0x40]; float f68; char pad6C[4]; float f70;
};
struct Type { char pad0[0x14]; Shape *shape; char pad18[4]; Program *program; };
struct Self { Owner *owner; Type *type; char pad8[0x50 - 8]; char dl[0xC]; int s5C; int s60; };
struct Particle {
    char pad0[0x10]; Owner *owner; float g14, g18; int g1C; char pad20[4]; float s24, s28; char pad2C[4]; qword v30;
    Matrix m; char pad70[0x90 - 0x70]; qword v90; qword vA0; qword vB0; float fC0, fC4; char padC8[0xE8 - 0xC8]; VTE *vt;
};
struct Batch { int count; qword *pos; qword *vel; float *a; float *b; };
struct SW { char pad[8]; };
extern SW D_00475480;
extern qword D_00317550;
extern "C" {
Particle *func_0020B9C0(SW *, int, void *);
float func_0011E940(float, float);
}
static inline qword Length(qword v)
{
    qword d, one, len;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(len) : "j"(d));
    return len;
}
static inline float X(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline qword Unit(qword v, qword len)
{
    qword r;
    __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(len));
    return r;
}
static inline qword Normalize(qword v, qword fallback)
{
    qword len = Length(v);
    if (X(len) < 0.0001f)
        return fallback;
    return Unit(v, len);
}
extern "C" void func_00202330(Self *self, Batch *batch)
{
    Type *type = self->type;
    Program *prog = type->program;
    Shape *shape = type->shape;
    for (int i = 0; i < batch->count; i++) {
        Particle *p = func_0020B9C0(&D_00475480, prog->id, self->dl);
        if (!p)
            continue;
        VTE *e = &p->vt[1];
        void *thisp = (char *)p + e->d;
        qword pos = batch->pos[i];
        float g = func_0011E940(prog->rangeMin, prog->rangeMax);
        ((void (*)(void *, qword, float))e->pfn)(thisp, pos, g);
        p->owner = self->owner;
        if (shape->s24 != 0.0f || shape->s28 != 0.0f) {
            p->s24 = shape->s24;
            p->s28 = shape->s28;
        }
        p->v90 = batch->vel[i];
        float a = batch->a[i];
        p->g14 = a;
        p->g18 = batch->b[i] - a;
        p->v30 = shape->v30;
        p->vA0 = shape->origin;
        qword *dst = &p->vB0;
        *dst = Normalize(shape->axis, D_00317550);
        p->fC0 = shape->f70;
        p->fC4 = shape->f68;
        p->g1C = self->s5C;
        Owner *owner = self->owner;
        if (owner->frame) {
            VTE *fe = &owner->frame->vt[36];
            p->m = *((Matrix *(*)(void *))fe->pfn)((char *)owner->frame + fe->d);
        } else {
            Matrix *m = &owner->local;
            p->m = *m;
        }
        VTE *e2 = &p->vt[2];
        ((void (*)(void *, Program *, int))e2->pfn)((char *)p + e2->d, prog, self->s60);
    }
}
