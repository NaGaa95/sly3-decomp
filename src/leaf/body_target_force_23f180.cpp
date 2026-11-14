// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-gcse
// func_0023F180: pull the owner body toward a target position and/or velocity (Sly 3 version of Sly 2 func_001F5E10, the
// sibling of body_steer_force_23efa0.cpp). For each error vector d (target position - current translation, target velocity -
// current velocity) of length l > 0.0001 the gain c*l + b + a/l (velocity gain clamped to 1/dt) scales d, converted into the
// parent space by func_0028E990, and the result is added to the owner's force. As in the sibling, the gain is also stored to
// a stack holder (scalar) that is never read back.
// Compiler notes (each choice is measured):
//  - -fno-gcse keeps the entry copy of the target velocity: its spilled pseudo then gets the slot after the first block's force
//    and gain (0x40) instead of being replaced by the parameter.
//  - the qwords that live across a call (target position/velocity, force copies, gains) are plain qword pseudos: reload spills
//    them, which gives the GPR lq/sq copies through v0 and the vf2/vf3/vf4 reloads in front of AddScaled.
//  - Scalar and Sub use the g++ named return value so the asm writes the caller's variable directly (no copy pseudo): the gain
//    keeps its own pseudo number (stack slot order) and the second difference needs no vmove.
//  - "=r,j" on the gain lets regclass prefer the VU class (so the pseudo is spilled instead of taking a callee-saved GPR) while
//    the output reload still picks a GPR for mfc1.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } V;
struct M4 { qword r[4]; };
struct COEF { float a, b, c; };
struct VE { short d, pad; void *fn; };
struct OWNER { char pad[0xA0]; void *parent; char padA4[0x4C]; qword force; };
struct S { char pad[0xC]; VE *vt; char pad10[0x38]; OWNER *owner; };
struct CLOCK { float time, dt; };
extern CLOCK D_0036BB98;
extern "C" {
qword func_0028E990(void *, void *, qword);
void func_0023F180(S *p, qword position, COEF *pc, qword velocity, COEF *vc);
}
static inline M4 *Matrix(S *p) { VE *e = &p->vt[36]; return ((M4 *(*)(void *))e->fn)((char *)p + e->d); }
static inline qword Velocity(S *p) { VE *e = &p->vt[38]; return ((qword (*)(void *))e->fn)((char *)p + e->d); }
static inline qword Sub(qword x, qword y) return r { __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(x), "j"(y)); }
static inline float Length(qword v)
{
    qword r, one; float f;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(r), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(r) : "j"(r));
    __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(r));
    return f;
}
static inline qword Scalar(float f) return r { __asm__("mfc1 %0,%1" : "=r,j"(r) : "f,f"(f)); }
static inline qword AddScaled(qword old, qword dir, qword scale)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%3,%2x" : "=&j"(r) : "j"(old), "j"(scale), "j"(dir));
    return r;
}

void func_0023F180(S *p, qword position, COEF *pc, qword velocity, COEF *vc)
{
    V scalar;
    qword old1, scale1, speed, old2, scale2;
    OWNER *owner = p->owner;
    /* pin: the parent load goes straight into the argument register, so the scheduler keeps it after the force copy */
    register void *parent __asm__("$5");
    speed = velocity;
    if (pc) {
        qword difference = Sub(position, Matrix(p)->r[3]);
        float distance = Length(difference);
        if (1.0e-4f < distance) {
            float value = (pc->c * distance + pc->b) + pc->a / distance;
            old1 = owner->force; parent = owner->parent;
            scale1 = Scalar(value); scalar.q = scale1;
            owner->force = AddScaled(old1, func_0028E990(0, parent, difference), scale1);
        }
    }
    if (vc) {
        qword difference = Sub(speed, Velocity(p));
        float distance = Length(difference);
        if (1.0e-4f < distance) {
            float value = (vc->c * distance + vc->b) + vc->a / distance;
            float limit = 1.0f / D_0036BB98.dt;
            if (limit < value) value = limit;
            old2 = owner->force; parent = owner->parent;
            scale2 = Scalar(value); scalar.q = scale2;
            owner->force = AddScaled(old2, func_0028E990(0, parent, difference), scale2);
        }
    }
}
