// Find the nearest other object in the global list (objects of the caller's group and finished objects are skipped) by squared distance between their vtable slot 36 positions.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Method { short delta, reserved; void *(*call)(void *); };
struct Matrix { unsigned char opaque00[0x30]; qword position; };
struct Candidate {
    unsigned char opaque00[0xC];
    Method *methods;
    unsigned char opaque10[0x1B0 - 0x10];
    int mode;
    unsigned char opaque1B4[4];
    int state;
    unsigned char opaque1BC[0x1C8 - 0x1BC];
    int group;
    int owner;
    unsigned char opaque1D0[0x554 - 0x1D0];
    Candidate *next;
};
struct List { Candidate *first; Candidate *last; int linkOffset; };
extern "C" void func_002BEE98(void *object, int flags);
struct Guard {
    int storage[4];
    ~Guard() { func_002BEE98(this, 2); }
};
extern "C" {
extern List D_00479BEC;
extern const float D_00325CC4;
}
#define MATRIX(o) ((Matrix *)(o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
static __inline__ qword LengthSquared(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    return d;
}
static __inline__ float GetX(qword v) { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(v)); return g; }
extern "C" Candidate *func_00218E98(Candidate *self)
{
    Guard guard;
    Candidate *best = 0;
    float bestDistance = D_00325CC4;
    Candidate *other;
    for (other = D_00479BEC.first; other; other = other->next) {
        if (other == self) continue;
        if (self->group == other->group && self->group != 0) continue;
        if (other->owner != 0 && other->owner != self->group && self->mode == 2) continue;
        if (other->state == 2) continue;
        {
            qword here = MATRIX(self)->position;
            qword diff;
            register qword there asm("vf2") = MATRIX(other)->position; /* register pin: other position in vf2 like the target */
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(diff) : "j"(here), "j"(there));
            float distance = GetX(LengthSquared(diff));
            if (distance < bestDistance) {
                bestDistance = distance;
                best = other;
            }
        }
    }
    return best;
}
