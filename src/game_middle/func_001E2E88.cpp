// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Mode change of the actor in state 0x16.
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Clock { float time, step; };
union Vector { qword q; float f[4]; };
struct Vec3 { float x, y, z; };
struct Vec16 { float x, y, z, w; } __attribute__((aligned(16)));
struct Tuning { unsigned char pad0[0x1C]; float jump; };
struct Trail { float x0; Vec16 *b; Vec16 *a; };
struct Rig {
    unsigned char pad0[8];
    float limit;
    unsigned char padC[8];
    Trail *trail;
    unsigned long flags;
    unsigned char pad20[0x88 - 0x20];
    int count;
    qword *points;
    unsigned char pad90[0xBC - 0x90];
    int b0, b1;
};
struct Target { unsigned char pad0[0x28]; unsigned long flags; };
struct LO {
    char pad[12];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual qword *Frame();
    virtual void v36();
    virtual qword Velocity();
    virtual void v38();
    virtual void SetVelocity(qword v);
};
typedef LO Object;
struct Anim { unsigned char pad0[0x14]; void *resource; };
struct Actor : LO {
    unsigned char gap10[0x10C - 0x10];
    Tuning *tuning;
    unsigned char gap110[0x1A0 - 0x110];
    Vec3 push;
    unsigned char gap1AC[0x1B8 - 0x1AC];
    int phase;
    unsigned char gap1BC[0x218 - 0x1BC];
    int airborne;
    unsigned char gap21C[0x288 - 0x21C];
    Rig *rig;
    unsigned char gap28C[0x113C - 0x28C];
    Anim *anim;
    int x1140;
    unsigned char gap1144[0x1AD4 - 0x1144];
    int mode;
    float entered;
    Trail *trail;
    float savedJump;
    void *sound;
    Object *partner;
    Target *target;
    unsigned char gap1AF0[0x1AF8 - 0x1AF0];
    void *anchor;
    unsigned char gap1AFC[0x1B10 - 0x1AFC];
    void *body;
    unsigned char gap1B14[0x1B18 - 0x1B14];
    float blend;
    float height;
    unsigned char gap1B20[0x1B38 - 0x1B20];
    float rise;
};
extern "C" {
extern Clock D_0036BB98;
extern float D_00324A28;
extern char D_003174C0[];
void func_0023EC98(Actor *self, int n);
void func_0023DF78(Actor *self);
void func_001DCCF0(Actor *self, float v);
void func_001E2A20(Actor *self, void *object);
qword func_001205F0(qword v, float limit);
void func_002412C8(Target *t, float v);
void func_0012F670(void *body, void *m);
float func_002A3EE8(float y, float x);
void func_0024E878(Actor *self, float angle);
void func_00277C08(Actor *self, int a, int b, int c, qword position, float g);
void func_0023AC58(void *p);
void func_00137588(void *anim, void *recv, int flags, void **out, float t, float rate);
}
static inline float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static inline qword MakeW(float x, float y, float z)
{
    qword q = Make(x, y, z);
    // Keep the packed velocity in its stack home before the virtual call.
    volatile qword home = q;
    return q;
}
extern "C" void func_001E2E88(Actor *self, int newMode)
{
    if (self->mode == newMode)
        return;
    switch (self->mode) {
    case -1: {
        Rig *rig = self->rig;
        rig->flags |= 0x20000;
        self->rig->limit = 75.0f;
        self->trail = self->rig->trail;
        self->rig->trail = 0;
        self->phase = 2;
        Vec3 *push = &self->push;
        push->z = 0.0f;
        push->y = 0.0f;
        push->x = 0.0f;
        func_0023EC98(self, 0);
        self->savedJump = self->tuning->jump;
        self->tuning->jump = -1.0f;
        qword v = self->Velocity();
        float x = GetX(v);
        float y = GetY(v);
        float z;
        if (self->airborne == 0)
            z = GetZ(v) + 300.0f;
        else
            z = 600.0f;
        qword velocity = MakeW(x, y, z);
        self->SetVelocity(velocity);
        self->height = D_00324A28;
        break;
    }
    case 2:
        func_0023DF78(self);
        break;
    }
    self->mode = newMode;
    self->entered = D_0036BB98.time;
    void *handle = 0;
    int flags = 1;
    switch (newMode) {
    case -1: {
        self->rig->flags &= ~0x20000UL;
        self->rig->trail = self->trail;
        qword *p = self->rig->points;
        int i = 0;
        if (i < self->rig->count) do {
            p[i] = func_001205F0(p[i], self->rig->limit);
            Vec16 *e = (Vec16 *)(i * 16 + (int)self->trail->a);
            e->z = 0.0f;
            e->y = 0.0f;
            e->x = 0.0f;
            Vec16 *f = (Vec16 *)(i * 16 + (int)self->trail->b);
            f->z = 0.0f;
            f->y = 0.0f;
            f->x = 0.0f;
            self->trail->x0 = 0.0f;
            i++;
        } while (i < self->rig->count);
        Rig *r = self->rig;
        r->b1 = -1;
        r->b0 = -1;
        self->phase = 0;
        func_0023EC98(self, 1);
        if (self->target && ((int)(self->target->flags >> 56) & 1))
            func_002412C8(self->target, 0.25f);
        if (self->body)
            func_0012F670(self->body, D_003174C0);
        if (self->partner) {
            self->partner->v8();
        }
        self->tuning->jump = self->savedJump;
        self->blend = 0.0f;
        func_001DCCF0(self, 1.0f);
        qword *f = self->Frame();
        float *ff = (float *)f;
        func_0024E878(self, func_002A3EE8(ff[1], ff[0]));
        break;
    }
    case 0:
        handle = self->sound;
        flags = 9;
        break;
    case 1:
        handle = self->sound;
        flags = 9;
        if (2500.0f < self->rise) {
            func_00277C08(self, 0x400, 0x28, 0, self->Frame()[3], 225.0f);
            func_001E2A20(self, self->anchor);
        }
        break;
    case 2:
        func_0023DF78(self);
        break;
    }
    if (self->mode == -1)
        return;
    func_0023AC58(&self->x1140);
    if (self->anim == 0 || self->anim->resource != handle)
        func_00137588(handle, self, flags, (void **)&self->anim, 0.0f, 1.0f);
}
