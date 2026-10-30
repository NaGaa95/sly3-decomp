// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 2 reference: /home/claude/decomp src/hand/func_0014F268.c (matrix multiply replaced by a call).
typedef int qword __attribute__((mode(TI)));
struct CM { char pad[0x138]; float sx, sy; };
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
qword func_001C9428(struct CM *p, int k, qword v);
qword func_00167838(struct CM *p, qword v)
{
    union { qword q; float f[4]; } r;
    float x = GetX(v);
    float z = GetZ(v);
    float y = GetY(v);
    r.f[0] = z;
    r.f[2] = y;
    r.f[1] = -x;
    if (z > 1e-4f) {
        r.f[1] = -x * z;
        r.f[2] = y * z;
    }
    r.f[1] *= p->sx;
    r.f[2] *= p->sy;
    return func_001C9428(p, 0, r.q);
}
