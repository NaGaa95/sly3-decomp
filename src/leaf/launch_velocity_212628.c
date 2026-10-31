// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Launch velocity reaching "to" from "from" in dt seconds under gravity.z: lateral part is the offset minus its D_00317550-axis component over dt, axis part (dz - g*dt*dt/2)/dt.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } UQ;
extern qword D_00317550;
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Dot3(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword ScaleX(qword v, qword s)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s));
    return r;
}
static inline qword MulAdd(qword a, qword sa, qword b, qword sb)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(a), "j"(sa), "j"(b), "j"(sb));
    return r;
}
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static __inline__ qword Qmtc2(float g)
{
    qword v;
    __asm__("qmtc2.ni %1, %0" : "=j"(v) : "r"(g));
    return v;
}
qword func_00212628(qword from, qword to, qword gravity, float dt)
{
    qword d = Sub(to, from);
    float vertical = (GetZ(d) - 0.5f * dt * dt * GetZ(gravity)) / dt;
    qword up_part = ScaleX(D_00317550, Dot3(d, D_00317550));
    UQ scratch;
    qword inverse;
    scratch.q = Qmtc2(1.0f / dt);
    inverse = scratch.q;
    d = Sub(d, up_part);
    scratch.q = Qmtc2(vertical);
    return MulAdd(d, inverse, D_00317550, scratch.q);
}
