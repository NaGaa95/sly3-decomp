// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Mode 2/4 update: in mode 2 walks the global object list for a neighbour inside the outer/inner radius (guard object released after the walk), selects the fx hook, then steers the goal (spring through func_0011E598).
typedef int qword __attribute__((mode(TI)));
struct Method { short delta, reserved; void *(*call)(void *); };
struct Matrix { unsigned char opaque00[0x30]; qword position; };
struct Actor { unsigned char pad0[0x18]; unsigned int flags; };
struct SMP { float a, b, c; };
struct Goal { unsigned char pad0[4]; float g4; unsigned char pad8[4]; SMP smp; float g18; };
struct Frame { qword r0, r1, r2; unsigned char pad30[0xB0 - 0x30]; qword v; };
struct Fx { unsigned char pad0[0xC]; Method *methods; };
struct Node;
struct Self {
    unsigned char pad00[0xC]; Method *methods;
    unsigned char pad10[0x4C - 0x10]; Frame *frame;
    unsigned char pad50[0x134 - 0x50]; Actor *actor;
    unsigned char pad138[0x1B0 - 0x138]; int mode;
    unsigned char pad1B4[0x1D0 - 0x1B4]; Self *owner;
    unsigned char pad1D4[0x1DC - 0x1D4]; Goal *goal;
    unsigned char pad1E0[0x22C - 0x1E0]; float g22C;
    unsigned char pad230[0x428 - 0x230]; float outer, inner;
    Fx *fx;
    unsigned char pad434[0x448 - 0x434]; void *p448;
    unsigned char pad44C[0x554 - 0x44C]; Self *next;
};
struct List { Self *first; Self *last; int linkOffset; };
struct CLOCK { float now, step; };
extern "C" void func_002BEE98(void *object, int flags);
struct Guard {
    int storage[4];
};
extern "C" {
extern List D_00479BEC;
extern CLOCK D_0036BB98;
extern unsigned char D_00475480[];
extern void *D_00468D24;
int func_001A7A80(Actor *, int, float);
void func_002159D8(Self *, int);
int func_001A9478(void *, int);
void func_0021A068(void *, Self *);
int func_00260758(Fx *, int);
float func_0011E598(float, float, float, void *, float *);
void func_002155F0(Self *);
}
#define MATRIX(o) ((Matrix *)(o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
static __inline__ qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static __inline__ qword LengthSquaredXY(qword v)
{
    qword d;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(v));
    return d;
}
static __inline__ float GetX(qword v) { qword t; float f; __asm__("qmfc2.ni %0, %1" : "=r"(t) : "j"(v)); __asm__("mtc1 %1, %0" : "=f"(f) : "r"(t)); return f; }
// M * v (rows of M dotted with v)
static inline qword QwMulM3(Frame *pm, qword v)
{
    qword r = pm->r0;
    qword t0, t1, t2, one;
    __asm__("vmul.xyzw %2,%0,%5\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\tvmul.xyzw %3,%6,%5\n\tvmul.xyzw %4,%7,%5\n\tvadday.x $ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\tvaddax.y $ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\tvaddax.z $ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y"
            : "+j"(r), "=&j"(one), "=&j"(t0), "=&j"(t1), "=&j"(t2) : "j"(v), "j"(pm->r1), "j"(pm->r2));
    return r;
}
union UQ { qword q; float f[4]; };
extern "C" void func_00216350(Self *self)
{
    Actor *actor;
    Guard guard;
    SMP smp;
    UQ local;
    switch (self->mode) {
    case 2:
        actor = self->actor;
        break;
    case 4:
        actor = self->owner->actor;
        break;
    default:
        return;
    }
    int blocked = 0;
    if (self->mode == 2) {
        if (func_001A7A80(actor, 0x6D0, 0.1f)) {
            if (self->p448) {
                func_002159D8(self, 3);
                return;
            }
        }
        int found = 0;
        {
            float outerSq = self->outer * self->outer;
            float innerSq = self->inner * self->inner;
            Self *other;
            for (other = D_00479BEC.first; other; other = other->next) {
                if (other == self) continue;
                if (other->mode == 7) continue;
                qword here = MATRIX(self)->position;
                qword there = MATRIX(other)->position;
                float d = GetX(LengthSquaredXY(Sub(here, there)));
                if (outerSq < d) continue;
                if (d < innerSq) {
                    found = 1;
                    goto done;
                }
                if (func_001A7A80(actor, 0x20, 0.1f)) {
                    found = 1;
                done:
                    blocked = 0;
                    break;
                }
                blocked = 1;
            }
            func_002BEE98(&guard, 2);
        }
        if (found) {
            if (!func_001A9478(D_00475480, -1))
                func_0021A068(D_00468D24, self);
        }
    }
    if (self->fx) {
        if (blocked) {
            if (!func_00260758(self->fx, 0x37B)) {
                Method *m = &self->fx->methods[56];
                m->call((unsigned char *)self->fx + m->delta);
            }
        } else {
            Method *m = &self->fx->methods[54];
            m->call((unsigned char *)self->fx + m->delta);
        }
    }
    float dir = 0.0f;
    if (actor->flags & 1)
        dir = 1.0f;
    if (actor->flags & 2)
        dir = dir - 1.0f;
    smp = self->goal->smp;
    float gain = self->goal->g18;
    if (dir != 0.0f) {
        local.q = QwMulM3(self->frame, self->frame->v);
        if (local.f[2] * dir < 0.0f)
            smp.a = smp.a * 2.5f;
    } else {
        smp.a = smp.a * 2.5f;
    }
    self->g22C = func_0011E598(self->g22C, dir * gain, D_0036BB98.step, &smp, 0);
    func_002155F0(self);
}
