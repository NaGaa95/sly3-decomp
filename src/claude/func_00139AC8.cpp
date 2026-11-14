// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Segment store; VU_FLOAT has a ctor so its temp lives on the stack; D_00317550 is a struct so the vD0 store forces its reload.
typedef int qword __attribute__((mode(TI)));
struct P { char pad[0xC8]; float gC8; int padCC; qword vD0; qword vE0; };
extern "C" {
extern struct VQ { qword q; } D_00317550;
void func_00139AC8(P *p, qword a, qword b, float g);
}
static inline float Dist(qword a, qword b)
{
    qword d, m, one, l;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(m), "=j"(one) : "j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(m));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
    return g;
}
struct VU_FLOAT { qword q; VU_FLOAT(const VU_FLOAT &s) { q = s.q; } VU_FLOAT(float f) { qword t; __asm__("qmtc2.ni %1, %0" : "=j"(t) : "r"(f)); q = t; } };
static inline qword AddScaled(qword a, qword v, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(r) : "j"(a), "j"(s.q), "j"(v));
    return r;
}
void func_00139AC8(P *p, qword a, qword b, float g)
{
    p->gC8 = g;
    p->vD0 = a;
    p->vE0 = b;
    if (Dist(a, b) < 10.0f) {
        p->vD0 = AddScaled(a, D_00317550.q, VU_FLOAT(-10.0f));
        p->vE0 = AddScaled(b, D_00317550.q, VU_FLOAT(10.0f));
    }
}
