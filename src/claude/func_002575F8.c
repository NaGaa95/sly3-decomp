// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x250]; qword v250; qword v260; char pad2[0x112C - 0x270]; int k; char pad3[0x11D8 - 0x1130]; void *p11D8; int pad11DC; float f11E0; };
void func_0012F4F8(void *, qword);
static inline qword Splat(float g)
{
    /* the float's GPR copy is widened in place, then broadcast into all four lanes */
    float t = g;
    qword r;
    __asm__("pextlw %0, %0, %0" : "+r"(t));
    __asm__("pextlw %0, %1, %1" : "=r"(r) : "r"(t));
    return r;
}
static inline qword Scale(qword v, float g)
{
    union { qword q; float f; } s;
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(g));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s.q));
    return r;
}
void func_002575F8(struct S *p, float g)
{
    if (p->p11D8) {
        p->f11E0 = g;
        if (p->k != 14 && p->k != 16)
            func_0012F4F8(p->p11D8, Splat(g));
        p->v260 = Scale(p->v250, g);
    }
}
