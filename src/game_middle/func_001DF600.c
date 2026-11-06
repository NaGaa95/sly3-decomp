// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
// Enters state k (-1, 0, 1 or 2) of the actor: clears the stored direction, releases or hands over the attached
// contact list and restarts the clip. State 1 flattens the vertical velocity.
// Allocation notes: the contact sides are taken as pointers b before a (decides the s0/s1 priority of self vs pair); the
// method pointer and `this` of the second virtual call are read before the scalar union is written, so the stack store
// sorts after those loads; xC is read into a local before the call.
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Clock { float time, step; };
struct Contact {
    int x0, x4;
    struct Contact *owner;
    int xC;
    qword v10;
    unsigned char pad20[0x10];
    qword v30;
};
struct ContactPair {
    struct Contact side[2];
    unsigned char gap80[0xAC - 0x80];
    struct ContactPair *next;
};
struct Anim { unsigned char prefix[0x14]; void *clip; };
struct Actor {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x113C - 0x10];
    struct Anim *anim;
    unsigned char gap1140[0x1408 - 0x1140];
    float landed;
    unsigned char gap140C[0x1528 - 0x140C];
    int state;
    float changed;
    unsigned char gap1530[4];
    struct ContactPair *contacts;
};
extern struct Clock D_0036BB98;
extern char D_00475480[];
extern qword D_00317550;
void func_001CBAA0(void *world, struct ContactPair *contacts);
void func_00240CB0(void *actor, int a, int b, int c, int d, int e, qword p, qword q, int f);
float *func_00136880(void *clip, int id);
void func_00137D08(struct Anim *anim, int a, int b, float x, float y);
void func_00137B00(struct Anim *anim);
static inline qword BlendScalar(float value)
{
    qword scalar;
    __asm__("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(value));
    return scalar;
}
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword ScaleX(qword v, qword s) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(s)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword AddScaled(qword base, qword direction, qword scale)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base), "j"(direction), "j"(scale));
    return r;
}
void func_001DF600(struct Actor *self, int k)
{
    union { qword q; float f[4]; } scalar;
    if (self->state == k)
        return;
    if (self->state == -1) {
        float *direction = (float *)((char *)self + 0x1A0);
        direction[2] = 0.0f;
        direction[1] = 0.0f;
        direction[0] = 0.0f;
    }
    self->state = k;
    self->changed = D_0036BB98.time;
    switch (k) {
    case 0:
        break;
    case -1:
        func_001CBAA0(D_00475480, self->contacts);
        self->contacts = 0;
        break;
    case 1: {
        qword velocity = ((qword (*)(void *))self->methods[38].function)((char *)self + self->methods[38].adjustment);
        qword up = D_00317550;
        qword flat = Sub(velocity, ScaleX(up, Dot(velocity, up)));
        struct Method *method = &self->methods[40];
        void (*fn)(void *, qword) = (void (*)(void *, qword))method->function;
        void *target = (char *)self + method->adjustment;
        scalar.q = BlendScalar(-500.0f);
        fn(target, AddScaled(flat, up, scalar.q));
        self->landed = D_0036BB98.time;
        break;
    }
    case 2: {
        float *direction = (float *)((char *)self + 0x1A0);
        struct ContactPair *pair;
        direction[2] = 0.0f;
        direction[1] = 0.0f;
        direction[0] = 0.0f;
        for (pair = self->contacts; pair; pair = pair->next) {
            int side = pair->side[0].owner != (struct Contact *)self;
            struct Contact *b = &pair->side[side];
            struct Contact *a = &pair->side[1 - side];
            int xC = a->xC;
            func_00240CB0(self, 0, xC, 4, 0x14, 0, a->v10, b->v30, 0);
        }
        func_001CBAA0(D_00475480, self->contacts);
        self->contacts = 0;
        {
            float *time = func_00136880(self->anim->clip, 0x1C6);
            if (time)
                func_00137D08(self->anim, 0, 0, *time, 1.0f);
            else
                func_00137B00(self->anim);
        }
        break;
    }
    }
}
