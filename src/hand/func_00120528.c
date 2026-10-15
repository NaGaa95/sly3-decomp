// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline float sqrtf_(float x) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
float func_002A3EE8(float y, float x);
float func_0011E3B8(float g);
void func_00120528(qword v, float *pradPan, float *pradTilt)
{
    if (pradPan)
        *pradPan = func_0011E3B8(func_002A3EE8(GetY(v), GetX(v)));
    if (pradTilt)
        *pradTilt = func_0011E3B8(func_002A3EE8(GetZ(v), sqrtf_(GetX(v) * GetX(v) + GetY(v) * GetY(v))));
}
