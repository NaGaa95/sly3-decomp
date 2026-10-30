// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Sphere overlap test: (|a.xyz - b.xyz|^2 < (a.w + b.w)^2); Copy/GetW/Dot3 are VU lane helpers. */
typedef int qword __attribute__((mode(TI)));
static __inline__ qword Copy(qword v) { qword r; __asm__("vmax.xyzw %0,%0,%0" : "=j"(r) : "0"(v)); return r; }
static __inline__ float GetW(qword q)
{
    int n;
    qword t;
    union { int i; float f; } u;
    __asm__("qmfc2.ni %0, %1" : "=r"(t) : "j"(q));
    __asm__("pextuw %0,$0,%1\n\tpextuw %0,$0,%0" : "=r"(n) : "r"(t));
    u.i = n;
    return u.f;
}
static __inline__ qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static __inline__ float Dot3(qword v)
{
    qword d, one;
    int n;
    union { int i; float f; } u;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("qmfc2.ni %0, %1" : "=r"(n) : "j"(d));
    u.i = n;
    return u.f;
}
int func_00120EE0(qword a, qword b)
{
    float r = GetW(a) + GetW(b);
    float d2 = Dot3(Sub(Copy(a), Copy(b)));
    if (d2 < r * r)
        return 1;
    return 0;
}
