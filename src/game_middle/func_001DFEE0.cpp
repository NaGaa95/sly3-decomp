// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Builds the two end points of a motion blend for the actor's current mode.
// Mode 0: the two probe points are the up/down scalings of D_00317550 mapped through func_0028E990.
// Mode 1: solves for the time to reach the goal (second root of the quadratic in z, clamped to [0.15, *pDuration]),
// seeks the clip by that time, then fills both outputs from the cubic-style blend of position, velocity and goal.
// Allocation notes:
// - Scale lists the VU_FLOAT operand first in its asm (swapped operand order gives the original vf numbering).
// - The VU_FLOAT temporaries are the dead sqc2 stores at sp+0x10 (and sp+0 in mode 0).
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT {
    qword qw;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "r"(f)); }
};
struct Clip { unsigned char pad0[0x40]; float rate; };
struct Source { unsigned char pad0[0x80]; qword target; };
struct Node {
    unsigned char pad0[0x30];
    qword position;
    unsigned char pad40[0xA0 - 0x40];
    int channel;
    unsigned char padA4[0xB0 - 0xA4];
    qword velocity;
};
struct Chain {
    unsigned char pad0[0x48];
    Node *node;
    unsigned char pad4C[0xD8 - 0x4C];
    Source *source;
};
struct Body { unsigned char pad0[0x190]; Chain *chain; };
struct Actor {
    unsigned char pad0[0x113C];
    Clip *clip;
    unsigned char pad1140[0x1540 - 0x1140];
    Body *body;
    unsigned char pad1544[0x1588 - 0x1544];
    int state;
};
extern "C" {
extern qword D_00317550;
qword func_0028E990(int a, int channel, qword v);
int func_0011EA28(float *out, float a, float b, float c);
void func_00137D08(Clip *clip, float t, float rate, int a, int b);
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword MulXq(qword a, qword s) { qword r; __asm__("vmulx.xyzw %0,%2,%1x" : "=j"(r) : "j"(s), "j"(a)); return r; }
static inline qword MulX(qword a, VU_FLOAT s) { return MulXq(a, s.qw); }
static inline qword MulAdd(qword a, VU_FLOAT s, qword b)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.qw));
    return r;
}
static inline qword Scale(qword v, VU_FLOAT s)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(s.qw), "j"(v));
    return r;
}
static inline float Clamp(float value, float low, float high)
{
    if (value < low)
        return low;
    if (high < value)
        return high;
    return value;
}
static inline float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
extern "C" void func_001DFEE0(Actor *self, qword target, float *pTime, float *pDuration, qword *pOut1, qword *pOut2)
{
    qword out1, out2;
    switch (self->state) {
    case 0: {
        int channel = self->body->chain->node->channel;
        out1 = func_0028E990(0, channel, MulX(D_00317550, VU_FLOAT(2500.0f)));
        out2 = func_0028E990(0, channel, MulX(D_00317550, VU_FLOAT(-2000.0f)));
        break;
    }
    case 1: {
        Chain *chain = self->body->chain;
        Node *node = chain->node;
        qword position = node->position;
        qword velocity = node->velocity;
        qword accel = func_0028E990(0, node->channel, chain->source->target);
        float roots[4];
        int count = func_0011EA28(roots, GetZ(accel) * 0.5f, GetZ(velocity), GetZ(position) - GetZ(target));
        float t;
        if (count == 0)
            t = 0.15f;
        else
            t = Clamp(roots[count - 1], 0.15f, *pDuration);
        func_00137D08(self->clip, *pTime - t * self->clip->rate, self->clip->rate, 0, 0);
        qword a = MulAdd(velocity, VU_FLOAT(t), accel);
        *pDuration = t;
        qword b = MulAdd(position, VU_FLOAT(t * 0.5f), Add(velocity, a));
        qword d = Scale(Sub(target, b), VU_FLOAT(t));
        out1 = Add(velocity, d);
        out2 = Add(a, d);
        break;
    }
    }
    *pOut1 = out1;
    *pOut2 = out2;
}
