// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Owner { unsigned char pad[0x1CC]; int active; };
typedef union { qword q; float f[4]; } U;
struct Ctx { unsigned char pad0[0x80]; U vel; int pad90; float scale; int flag; int kind; };
struct Self {
    unsigned char pad0[0x508]; int mode; int moving; int pad510; struct Owner *owner;
    unsigned char pad518[0xE40 - 0x518]; unsigned char partA[0x1010 - 0xE40];
    unsigned char partB[0x19E0 - 0x1010]; int state; unsigned char pad19E4[0x1E90 - 0x19E4];
    unsigned char partC[0x10];
};
void func_0024E400(struct Self *self, struct Ctx *c, void *arg);
void func_001BFA08(void *part, struct Ctx *c, void *arg);
void func_001C3D18(void *part, struct Ctx *c, void *arg);
void func_00140BE8(void *part, struct Ctx *c, void *arg);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline qword LengthXY(qword v)
{
    qword r;
    qword d;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(r) : "j"(d));
    return r;
}
static inline float Clamp(float v, float lo, float hi)
{
    if (v < lo) v = lo;
    else if (hi < v) v = hi;
    return v;
}
void func_001AA768(struct Self *self, struct Ctx *c, void *arg)
{
    func_0024E400(self, c, arg);
    switch (self->state) {
    case 9:
        func_001BFA08(self->partB, c, arg);
        break;
    case 8:
        if (c->kind != 14) break;
        if (self->mode != 3) break;
        if (!self->owner->active) break;
        c->flag = 0;
        if (self->moving) {
            c->scale = Clamp(GetX(LengthXY(c->vel.q)) / c->vel.f[2] + 0.5f, 0.5f, 1.5f);
        } else {
            c->scale = 0;
        }
        break;
    case 5:
        func_001C3D18(self->partA, c, arg);
        break;
    case 7:
        func_00140BE8(self->partC, c, arg);
        break;
    case 19:
        c->scale = 0;
        c->flag = 0;
        break;
    }
}
