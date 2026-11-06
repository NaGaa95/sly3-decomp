// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
// Variant of func_001C1550 for the two-sided contact setup: blend the weights of the active axes (the side switch picks them; side 1
// chooses the second axis from the sign of the acceleration), normalise, build the weighted sum of the axis directions as the new
// acceleration and publish the request.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } U;
struct Anim { char pad[0x40]; float rate; };
struct P {
    char pad0[0x190]; char pad190[0x10]; U acceleration; char pad1B0[0x113C - 0x1B0];
    struct Anim *anim; char pad1140[0x163C - 0x1140]; int side;
};
struct Entry { union { float value; int bits; } weight; int active; char pad8[8]; U direction; };
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
void func_001C1CA8(struct P *p, struct Entry *axes, void *request)
{
    int indices[5];
    U total, scalar;
    int i, count;
    register int bits __asm__("$9"); /* register pin: the bit temp of the rate move lives in t1 like the original */
    float rate, sum;
    if (!request)
        return;
    rate = p->anim->rate;
    for (i = 7; i >= 0; i--)
        axes[i].weight.value = 0.0f;
    switch (p->side) {
    case 0:
        indices[0] = 0; indices[1] = 1; indices[2] = 4; indices[3] = 5; count = 4;
        break;
    case 1:
        indices[0] = 0;
        if (p->acceleration.f[1] < 0.0f) indices[1] = 2; else indices[1] = 3;
        indices[2] = 6; indices[3] = 7;
        count = 4;
        break;
    default:
        indices[0] = 0; count = 1;
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
    for (i = 7; i >= 0; i--) {
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
}
