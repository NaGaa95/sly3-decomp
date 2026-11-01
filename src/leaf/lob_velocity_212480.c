// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Ballistic lob: launch velocity (xyz) that carries a projectile from start to end under acceleration acc.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float a[4]; };
extern qword D_00317550, D_00317560;
float func_002A35F8(float);
float func_002A3EE8(float, float);
float func_002A36E8(float);
float func_002A3408(float);
static inline float Sqrt(float x) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
static inline void Bc(union U *out, float f) {
    __asm__("qmtc2.ni %1, %0" : "=j"(out->q) : "r"(f));
}
static inline float Dot(const qword *a, qword b) {
    qword d, one; float r;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(*a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(d));
    return r;
}
static inline float Len(qword a) {
    qword d, one; float r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(d));
    return r;
}
static inline qword Norm(qword a) {
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(a));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q\n\tvdiv $Q, $vf0w, %0x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "+j"(d) : "j"(a));
    return d;
}
static inline qword Difference(qword end, const qword *start) { qword result; __asm__("vsub.xyzw %0,%1,%2" : "=j"(result) : "j"(end), "j"(*start)); return result; }
qword func_00212480(float g, qword start, qword end, qword acc)
{
    union U delta, vel, scalar;
    qword d, s, n, r;
    float k = func_002A35F8(g);
    float z, len, q;
    float numerator;
    register float angle __asm__("$f12"); // pin: keeps the clamped elevation angle in $f12
    d = Difference(end, &start);
    delta.q = d;
    z = delta.a[2];
    delta.a[2] = 0.0f;
    len = Len(delta.q);
    angle = func_002A3EE8(z, len);
    if (angle < 0.0f) angle = 0.0f;
    q = Dot(&acc, D_00317550);
    k = angle + (1.57079637051f - angle) * k;
    q = q / ((z - len * func_002A36E8(k)) * 2.0f);
    if (q <= 0.0f) return D_00317560;
    q = Sqrt(q);
    numerator = len * q;
    q = numerator / func_002A3408(k);
    vel.q = delta.q;
    vel.a[2] = len * func_002A36E8(k);
    Bc(&scalar, q);
    s = scalar.q;
    n = Norm(vel.q);
    __asm__("vmulx.xyzw %0, %1, %0x" : "+j"(s) : "j"(n));
    r = s;
    vel.q = r;
    return vel.q;
}
