// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Winding test of three packed points in the xy plane: -1, 0 or 1 by the signed area against +-1. */
typedef int qword __attribute__((mode(TI)));
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }

int func_001E6428(qword a, qword b, qword c)
{
    float area = (GetX(a) - GetX(b)) * (GetY(b) - GetY(c)) - (GetY(a) - GetY(b)) * (GetX(b) - GetX(c));
    if (area < -1.0f)
        return -1;
    if (area > 1.0f)
        return 1;
    return 0;
}
