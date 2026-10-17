// SLY3_CFLAGS: -Os -G0 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
inline float PackedVectorX(qword vector) {
    float scalar;
    asm("mtc1 %1,%0" : "=f"(scalar) : "r"(vector));
    return scalar;
}
inline float PackedVectorY(qword vector) {
    float scalar;
    asm("prot3w %0,%1" : "=r"(scalar) : "r"(vector));
    return scalar;
}
inline float PackedVectorZ(qword vector) {
    float scalar;
    asm("pextuw %0,$0,%1" : "=r"(scalar) : "r"(vector));
    return scalar;
}
extern "C" int func_0011E9F0(float, float, float);
extern "C" qword func_0016A750(void *self);
extern "C" qword func_0016A7E8(void *self);
static inline int PositionNear(qword first, qword second)
{
    return func_0011E9F0(PackedVectorX(first), PackedVectorX(second), 0.0001f) &&
           func_0011E9F0(PackedVectorY(first), PackedVectorY(second), 0.0001f) &&
           func_0011E9F0(PackedVectorZ(first), PackedVectorZ(second), 0.0001f);
}

extern "C" int func_0016AFB8(void *self)
{
    qword current = *(qword *)((char *)self + 0x40);
    qword target = func_0016A7E8(self);
    return PositionNear(current, target);
}
