// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
static __inline__ qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
struct S00475480 { char pad[0x4E1C]; float g0; float g1; };
extern struct S00475480 D_00475480;

qword func_00146A80(void)
{
    union { qword q; float f[4]; } v;
    float a = D_00475480.g0;
    v.q = Make(0.0f, 0.0f, (D_00475480.g1 - a) * 0.5f + a);
    return v.q;
}
