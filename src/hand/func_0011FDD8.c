// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
static __inline__ qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
void func_0011EB28(float g, float *ps, float *pc);
qword func_0011FDD8(float radPan, float radTilt, float r)
{
    union { qword q; float f[4]; } v;
    float sp, cp, st, ct;
    func_0011EB28(radPan, &sp, &cp);
    func_0011EB28(radTilt, &st, &ct);
    v.q = Make(ct * cp * r, ct * sp * r, st * r);
    return v.q;
}
