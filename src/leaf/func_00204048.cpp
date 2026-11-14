// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Per-frame update of the vehicle's drive state: state 1 derives the forward drive value from the actor's input and speed,
// states 2 and 3 steer along the path curve, state 4 blends the body back to its saved placement with a Hermite step and
// spins its orientation about the saved axis. The resulting drive value is then smoothed.
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta, pad; void *fn; };
struct Mat3 { qword rows[3]; };
struct Mat4 { Mat3 rot; qword position; };
struct CLQ { float g0, g1, g2, gUnused; };
struct CLOCK { float now, step; };
struct SMP { float fast, slow, dtFast; };
struct Actor { float input; char pad04[0x14]; unsigned int flags; };
struct Manager { char pad00[0x28]; unsigned long flags; };
struct Owner {
    char pad00[0xC]; VTE *vt; char pad10[0x134 - 0x10]; Actor *actor;
    char pad138[0x194 - 0x138]; int x194; float g198; char pad19C[0x1F4 - 0x19C]; int x1F4; float g1F8;
    char pad1FC[0x32C - 0x1FC]; float g32C, g330, g334; char pad338[4]; float g33C, g340, g344;
    char pad348[0x380 - 0x348]; int state; float stamp; int curve; float g38C, g390;
    char pad394[0x440 - 0x394]; CLQ speedCurve; float lo450, hi454;
    char pad458[0xC70 - 0x458]; Mat3 anchor; qword saved; float duration, angle; char padCB8[8]; qword axis;
};
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
extern CLOCK D_0036BB98;
extern Manager *D_00479A64;
extern const qword D_00325880;
extern const qword D_00317560;
extern const SMP D_003256F8;
extern "C" {
void func_002075E8(Owner *, int);
int func_001A7A80(Actor *, int, float);
void *func_002459F8(int);
void func_00244F08(void *, Owner *);
void *func_001F4A80(Owner *);
void func_00168670(void *, int);
void func_0022EEA0(int, qword, int, int, int, int, float *, float);
float func_0022E0B8(int, float);
void func_0022E330(int, qword *, void *, float);
qword func_001C9428(void *, void *, qword);
float func_002A3EE8(float, float);
float func_0011E3B8(float);
float func_0011E560(float, float);
float func_0011E598(float, float, float, const SMP *, float *);
void func_00118558(float, float, float, qword, qword, qword, qword, qword *, qword *, qword *);
Mat3 *func_0011C8C0(Mat3 *, qword, float);
}
static inline qword Length(qword v)
{
    qword d, one, len;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(len) : "j"(d));
    return len;
}
static inline float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static inline float GClampR(float g, float gMin, float gMax) { if (g < gMin) return gMin; if (gMax < g) return gMax; return g; }
static inline float Curve(const CLQ &c, float t) { return c.g0 + t * (c.g1 + t * c.g2); }
static inline float Max(float a, float b) { return a > b ? a : b; }
// Virtual methods of the owner (vtable at +0xC).
static inline VTE *Slot(Owner *o, int i) { return &o->vt[i]; }
static inline Mat4 *Xf(Owner *o)
{
    VTE *e = Slot(o, 36);
    return ((Mat4 *(*)(void *))e->fn)((char *)o + e->delta);
}
static inline qword Velocity(Owner *o)
{
    VTE *e = Slot(o, 38);
    return ((qword (*)(void *))e->fn)((char *)o + e->delta);
}
static inline void SetPosition(Owner *o, qword v)
{
    VTE *e = Slot(o, 34);
    ((void (*)(void *, qword))e->fn)((char *)o + e->delta, v);
}
static inline void SetVelocity(Owner *o, qword v)
{
    VTE *e = Slot(o, 40);
    ((void (*)(void *, qword))e->fn)((char *)o + e->delta, v);
}
static inline void SetSpin(Owner *o, qword v)
{
    VTE *e = Slot(o, 41);
    ((void (*)(void *, qword))e->fn)((char *)o + e->delta, v);
}
static inline void SetOrientation(Owner *o, Mat3 *m)
{
    VTE *e = Slot(o, 35);
    ((void (*)(void *, Mat3 *))e->fn)((char *)o + e->delta, m);
}
// A float in the low word of a quadword held in a general register (the object itself is a dead stack copy). The "j"
// alternative only affects register allocation: the value then lives in its spill slot, as in the original.
struct FQ { qword q; FQ(float f) { __asm__("mfc1 %0,%1" : "=r,j"(q) : "f,f"(f)); } };
// A float in the low word of a VU register (the object itself is a dead stack copy).
struct VQ { qword q; VQ(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); } };
static inline qword Sub(const qword &a, const qword &b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Scale(qword a, qword s) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(s)); return r; }
// d*s1.x + v*s2.x + a*s3.x
static inline qword Blend(qword s1, qword d, qword s2, qword v, qword a, qword s3)
{
    qword r;
    __asm__("vmulax.xyzw $ACC,%2,%1x\n\tvmaddax.xyzw $ACC,%4,%3x\n\tvmaddx.xyzw %0,%5,%6x"
            : "=j"(r) : "j"(s1), "j"(d), "j"(s2), "j"(v), "j"(a), "j"(s3));
    return r;
}
static inline Mat3 Rotation(qword axis, float angle) return r { func_0011C8C0(&r, axis, angle); }
// rows of the product: r.rows[i] = a.rows[0]*b.rows[i].x + a.rows[1]*b.rows[i].y + a.rows[2]*b.rows[i].z
static inline Mat3 Mul(const Mat3 &a, const Mat3 &b) return r
{
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
            : "=j"(r.rows[0]) : "j"(a.rows[0]), "j"(a.rows[1]), "j"(a.rows[2]), "j"(b.rows[0]));
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
            : "=j"(r.rows[1]) : "j"(a.rows[0]), "j"(a.rows[1]), "j"(a.rows[2]), "j"(b.rows[1]));
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
            : "=j"(r.rows[2]) : "j"(a.rows[0]), "j"(a.rows[1]), "j"(a.rows[2]), "j"(b.rows[2]));
}
// State 4: move the body back to its saved placement over the remaining time with a Hermite step (`end` receives the
// end velocity of the step), clear its spin and turn the anchor orientation about the saved axis.
static inline void Settle(Owner *p, const Mat3 &anchor, VECTOR4 &end)
{
    VECTOR4 pos, vel;
    Mat3 spin, orientation;
    float remain = p->stamp + p->duration - D_0036BB98.now;
    float time = Max(remain, D_0036BB98.step);
    qword w1 = FQ(1.5f / time).q;
    qword saved = p->saved;
    qword delta = Sub(saved, Xf(p)->position);
    qword w2 = FQ(-0.5f).q;
    qword velocity = Velocity(p);
    qword w3 = VQ(0.25f).q;
    qword dt = VQ(time).q;
    qword gravity = Scale(D_00325880, dt);
    *(qword *)&end = Blend(w1, delta, w2, velocity, gravity, w3);
    float step = D_0036BB98.step;
    func_00118558(time, step, 1.0f, Xf(p)->position, Velocity(p), p->saved, *(qword *)&end, (qword *)&pos, (qword *)&vel, 0);
    SetPosition(p, *(qword *)&pos);
    SetVelocity(p, *(qword *)&vel);
    SetSpin(p, D_00317560);
    spin = Rotation(p->axis, p->angle * time / p->duration);
    orientation = Mul(spin, anchor);
    SetOrientation(p, &orientation);
}
extern "C" void func_00204048(Owner *p)
{
    int state;
    do {
        state = p->state;
        if (state == 4 && p->duration < D_0036BB98.now - p->stamp)
            func_002075E8(p, 1);
    } while (state != p->state);
    switch (state) {
    case 0:
        p->g344 = 0.0f;
        p->g33C = 0.0f;
        break;
    case 1: {
        if (p->x194 || p->x1F4) {
            p->g344 = -p->actor->input * p->g334;
            float speed = GetX(Length(Velocity(p)));
            float g = GClampR(Curve(p->speedCurve, speed), p->lo450, p->hi454);
            p->g344 = p->g344 * g;
        }
        int flagged = (D_00479A64->flags & (1UL << 56)) != 0;
        if (!flagged) {
            unsigned int flags = p->actor->flags;
            if (flags & 0x40)
                p->g33C = p->g32C;
            else if (flags & 0xA0)
                p->g33C = -p->g330;
            else
                p->g33C = 0.0f;
        } else {
            p->g33C = 0.0f;
        }
        if (func_001A7A80(p->actor, 0x200, 0.15f)) {
            void *fx = func_002459F8(0x2A);
            func_00244F08(fx, 0);
            func_00168670(func_001F4A80(p), 0);
        }
        break;
    }
    case 2:
    case 3: {
        VECTOR4 point;
        func_0022EEA0(p->curve, Xf(p)->position, 0, 0, 0, 0, &p->g38C, p->g38C);
        float length = func_0022E0B8(p->curve, p->g38C + p->g390);
        func_0022E330(p->curve, (qword *)&point, 0, length);
        qword local = func_001C9428(0, p, *(qword *)&point);
        float angle;
        if (p->state == 2)
            angle = func_002A3EE8(GetY(local), GetX(local));
        else
            angle = func_002A3EE8(GetY(local), -GetX(local));
        p->g344 = func_0011E560(func_0011E3B8(angle), p->g334);
        break;
    }
    case 4: {
        VECTOR4 end;
        Settle(p, p->anchor, end);
        p->g33C = 0.0f;
        break;
    }
    }
    if (p->state != 4)
        p->g340 = func_0011E598(p->g340, p->g344, D_0036BB98.step, &D_003256F8, 0);
    p->g1F8 = p->g340;
    p->g198 = p->g340;
}
/* Smoothing parameters read by func_00204E00 (same original translation unit). The original keeps them right after this
   function's jump table (0x325710, 8-byte aligned at 0x325728); defining them here makes the whole .rodata block
   0x325710..0x325740 one verifiable section (the assembler pads the table section to 16 bytes). */
extern const SMP D_00325728 = { 1.0f, 0.0f, 0.15f };
