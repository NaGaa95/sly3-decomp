// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
// Blend the weights of up to five contact axes from the acceleration (an animation-rate driven side switch picks which axes are
// active), normalise the weights, accumulate the weighted axis directions into a new acceleration and publish the request.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } U;
struct Anim { char pad[0x40]; float rate; };
struct P {
    char pad0[0x1A0]; U acceleration; char pad1B0[0x113C - 0x1B0];
    struct Anim *anim; int pad1140; int side;
};
struct Entry { union { float value; int bits; } weight; int active; char pad8[8]; U direction; };
struct Slot { int pad0; int tag; int *item; int pad0C[2]; };
struct Request { char pad0[0x90]; int count; struct Slot *slots; };
void func_00148938(void *);
static inline float FloatX(qword q) { int bits; float f; __asm__("qmfc2.ni %0,%1" : "=r"(bits) : "j"(q)); __asm__("mtc1 %1,%0" : "=f"(f) : "r"(bits)); return f; }
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3
	vaddw.x %1,$vf0,$vf0w
	vadday.x ACC,%0,%0y
	vmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
// Same dot product; the acceleration is listed twice, which raises its allocation priority over the first dot result.
static inline qword DotAccel(qword accel, qword dir)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3
	vaddw.x %1,$vf0,$vf0w
	vadday.x ACC,%0,%0y
	vmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(accel), "j"(dir), "j"(accel));
    return d;
}
// Low lane of a VU register as a float (the compiler moves the register to a GPR; the allocation-only operand ties the VU register).
static inline float LaneX(qword q) { float g; __asm__("mtc1 %1,%0" : "=f"(g) : "r"(q), "j"(q)); return g; }
static inline float Max(float a, float b) { float f; __asm__("max.s %0,%1,%2" : "=f"(f) : "f"(a), "f"(b)); return f; }
static inline qword AddScaled(qword v, qword x, qword k) { qword q; __asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(q) : "j"(v), "j"(x), "j"(k)); return q; }
static inline qword ScalarBits(int bits) { qword q; __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(bits)); return q; }
void func_001C1550(struct P *p, struct Entry *axes, struct Request *request)
{
    int indices[5];
    U total, scalar;
    int i, count, clear, accum, k;
    register int bits __asm__("$6"); /* register pin: the bit temp of the rate move lives in a2 like the original */
    float rate, sum;
    if (!request)
        return;
    rate = p->anim->rate;
    if (!axes[6].active || !axes[7].active)
        p->side = -1;
    else if (p->side == -1) {
        if (FloatX(Dot(p->acceleration.q, axes[0].direction.q)) < 0.0f)
            p->side = 1;
        else
            p->side = 0;
    }
    for (clear = 7; clear >= 0; clear--)
        axes[clear].weight.value = 0.0f;
    switch (p->side) {
    case -1:
        if (!axes[7].active) { indices[0] = 6; indices[1] = 2; indices[2] = 4; }
        else { indices[0] = 7; indices[1] = 3; indices[2] = 5; }
        indices[3] = 0; indices[4] = 1; count = 5;
        break;
    case 0:
        indices[0] = 6; indices[1] = 2; indices[2] = 4; indices[3] = 0; count = 4;
        break;
    case 1:
        indices[0] = 7; indices[1] = 3; indices[2] = 5; indices[3] = 1; count = 4;
        break;
    }
    sum = 0.0f;
    if (rate > 0.0f) {
        for (i = 1; i < count; i++) {
            struct Entry *entry = &axes[indices[i]];
            float denominator, along, w;
            denominator = rate * LaneX(Dot(entry->direction.q, entry->direction.q));
            along = LaneX(DotAccel(p->acceleration.q, entry->direction.q));
            w = Max(along / denominator, 0.0f);
            entry->weight.value = w;
            sum += w;
        }
    }
    {
        struct Entry *head = &axes[indices[0]];
        if (sum < 1.0f)
            head->weight.value = 1.0f - sum;
        else {
            head->weight.value = 0.0f;
            for (i = 1; i < count; i++)
                axes[indices[i]].weight.value /= sum;
        }
    }
    total.i[0] = total.i[1] = total.i[2] = 0;
    for (accum = 7; accum >= 0; accum--) {
        qword k = ScalarBits(axes->weight.bits);
        total.q = AddScaled(total.q, axes->direction.q, k);
        scalar.q = k;
        axes++;
    }
    {
        qword rk, q;
        __asm__("mfc1 %0,%1" : "=r"(bits) : "f"(rate));
        __asm__("qmtc2.ni %1,%0" : "=j"(rk) : "r"(bits));
        __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(q) : "j"(total.q), "j"(rk));
        scalar.q = rk;
        p->acceleration.q = q;
        func_00148938(request);
    }
    for (k = 0; k < request->count; k++) {
        struct Slot *slot = &request->slots[k];
        if (!slot->tag && *slot->item == 0x6F)
            ((float *)slot->item)[6] = sum;
    }
}
