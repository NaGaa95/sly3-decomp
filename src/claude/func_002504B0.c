// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; qword (*pfn)(void *); };
struct VT { char pad[0x130]; struct VTE e130; };
struct X { char pad[0xC]; struct VT *pvt; };
int func_0011EA28(float a, float b, float c, float *roots);
static __inline__ float SqrtF(float g) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(g)); return r; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static __inline__ float GMin(float a, float b) { return a < b ? a : b; }
float func_002504B0(struct X *px, float a, float b, float c)
{
    float s, ns, t0, m, t, h, d, T;
    float roots[2];
    {
        float a2 = a * -2.0f;
        s = SqrtF(c * a2);
    }
    ns = -s;
    t0 = ns / c;
    m = GetZ(px->pvt->e130.pfn((char *)px + px->pvt->e130.d));
    m = GMin(m, s);
    t = (m - s) / c;
    {
        float th = t * 0.5f;
        h = t * (s + c * th);
    }
    {
        float ba = (b - a) * -2.0f;
        float r = SqrtF(c * ba);
        func_0011EA28(c * 0.5f, r, a, roots);
    }
    d = roots[1] - t0;
    {
    float z = 0.0f;
    if (z < m) {
        float bh = (b - h) * -2.0f;
        return SqrtF(c * bh);
    }
    if (m < ns)
        h = z;
    }
    {
        register float Tp asm("$f0") = (t0 + t0 + d) - t; // pin: T in f0
        __asm__("" : "=f"(T) : "0"(Tp));
    }
    {
        float q = -h / T;
        float Th = T * 0.5f;
        return q - c * Th;
    }
}
