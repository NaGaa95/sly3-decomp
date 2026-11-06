// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// PosZoneSample (Sly 2 func_002215C0 without the arc branch).
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { qword r[3]; };
struct S { char pad[0x108]; void *curve; char pad1[0x11C - 0x10C]; int polar; };
extern "C" {
void func_0022E330(void *, float, qword *, qword *);
M3 func_0011CBF0(qword, qword);
qword func_0011FD70(float, float, float);
qword func_001C9428(void *, void *, qword);
extern qword D_00317550;
}
struct COEF { float a, b, c, d; };
struct BOUND { float low, high; };
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Rotate(const M3 &m, qword v)
{
    __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z" : "+j"(v) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return v;
}
extern "C" void func_00274390(S *p, float *times, COEF *coef, BOUND *bounds, float time, float delta, int mode, qword *out)
{
    U pos, normal, center;
    M3 m;
    U rotated;
    float *f = pos.f;
    int i;
    i = 2;
    do {
        float t = *times;
        float x = coef->a + t * (coef->b + t * coef->c);
        float lo = bounds->low, hi = bounds->high;
        if (x < lo) x = lo;
        else if (hi < x) x = hi;
        *f++ = x; times++; bounds++; coef++;
    } while (--i >= 0);
    if (mode == 2) pos.f[0] = -pos.f[0];
    if (p->polar) pos.q = func_0011FD70(pos.f[0], pos.f[1], pos.f[2]);
    if (p->curve) {
        func_0022E330(p->curve, mode != 1 ? time - delta : time + delta, &center.q, &normal.q);
        m = func_0011CBF0(normal.q, D_00317550);
        rotated.q = Rotate(m, pos.q);
    } else {
        center.i[0] = center.i[1] = center.i[2] = 0;
        pos.f[0] += delta;
        rotated.q = func_001C9428(p, 0, pos.q);
    }
    *out = Add(center.q, rotated.q);
}
