// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Evaluate and cap the contribution of each eligible view at the sphere.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } Vector;
struct View { unsigned char pad[0x10C]; int flags; };
struct Scene { unsigned char pad[0x3EB8]; int count; struct View *views[4]; };
int func_00167F60(struct View *view, qword pos, qword extent);
int func_00168048(struct View *view, qword pos, float *out, float g);

static inline qword Copy(qword v)
{
    qword r;
    __asm__("vmax.xyzw %0,%0,%0" : "=j"(r) : "0"(v));
    return r;
}

static inline qword HighWords(qword v)
{
    qword r;
    __asm__("pextuw %0,$0,%1" : "=r"(r) : "r"(v));
    return r;
}

static inline int WBits(qword v)
{
    int r;
    __asm__("pextuw %0,$0,%1" : "=r"(r) : "r"(HighWords(v)));
    return r;
}

static inline qword Widen(int n)
{
    qword r;
    __asm__("daddu %0,%1,$0" : "=r"(r) : "r"(n));
    return r;
}

static inline qword Min(qword a, qword b)
{
    qword r;
    __asm__("vmini.xyzw %0,%1,%0" : "=j"(r) : "j"(a), "0"(b));
    return r;
}

qword func_0018E500(struct Scene *scene, qword weights, int mask, qword pos, float g)
{
    Vector w, out;
    int i;
    out.i[3] = 0;
    out.i[2] = 0;
    out.i[1] = 0;
    out.i[0] = 0;
    w.q = weights;
    for (i = 0; i < scene->count; i++) {
        if (w.f[i] != 0.0f) {
            struct View *view = scene->views[i];
            if (view->flags & mask) {
                Vector extent;
                qword radius;
                // The center is read from VU0 directly into a1 after the radius is ready.
                register qword center __asm__("$5");
                extent.q = Widen(WBits(pos));
                center = Copy(pos);
                radius = extent.q;
                __asm__("" : "+r"(radius) : "j"(center));
                if (func_00167F60(view, center, radius))
                    func_00168048(view, Copy(*(qword *)&pos), &out.f[i], g);
            }
        }
    }
    return Min(out.q, weights);
}
