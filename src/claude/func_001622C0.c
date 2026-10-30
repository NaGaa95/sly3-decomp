// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static __inline__ qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
struct RECT { int left, top, right, bottom; };
struct P { char pad[0x160]; struct RECT rc; };
qword func_001622C0(struct P *p, qword v)
{
    union { qword q; float f[4]; } r;
    struct RECT *prc = &p->rc;
    int dx = prc->right - prc->left;
    int dy = prc->bottom - prc->top;
    float u = GetX(v) * 0.5f + 0.5f;
    float w = 0.5f - GetY(v) * 0.5f;
    r.q = Make(prc->left + u * dx, prc->top + w * dy, GetZ(v));

    return r.q;
}
