// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// (A49 draft) clamp of a planar length / heading; extra "j"(vv) operand and gcc-emitted z-lane qmfc2 (A64).
typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x70]; float f70; char a74[1]; };
float func_001205C8(qword);
float func_0011EE68(void *, float);
float func_0011FD70(float, float, float);
static inline float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline qword Get(qword v) { qword r; __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(v)); return r; }
static inline float GMin(float a, float b) { return a < b ? a : b; }
float func_00259208(struct S *p, qword v)
{
    qword vv, d;
    float h, len;
    __asm__("qmtc2.ni %1,%0" : "=j"(vv) : "r"(v));
    h = func_001205C8(Get(vv));
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=&j"(d) : "j"(vv), "j"(vv)); /* extra allocation-only operand: vv is caller-saved in its vf reg */
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("mtc1 %1,%0" : "=f"(len) : "r"(Get(d)));
    {
        float r = GMin(len, p->f70);
        return func_0011FD70(h, r, func_0011EE68(p->a74, GetZ(vv)));
    }
}
