// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
// Draw a ribbon quad for every active entry: orient it along (b - a), width scaled by the entry weight.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } U;
struct M4 { U r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct Obj { char pad[0xC]; struct VTE *vt; };
struct Game { char pad[0x3EB8]; int count; struct Obj *objs[1]; };
extern struct Game D_00475480;
qword *func_002BA818(qword *p, qword v);
qword func_001C8548(int index);
void func_001C8248(void *p, qword a, struct M4 *m, float s0, float s1);
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Cross(qword a, qword b) { qword r; __asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword LenV(qword v)
{
    qword l, t;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(l), "=&j"(t) : "j"(v), "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(l) : "0"(l));
    return l;
}
static inline float GetX(qword v) { float g; __asm__("qmfc2.ni %0,%1" : "=r"(g) : "j"(v)); return g; }
static inline qword Normalize(qword v) { qword l = LenV(v), r; __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q" : "=j"(r) : "j"(l), "j"(v)); return r; }
static inline qword Broadcast(float g) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(g)); return r; }
static inline qword Scale(qword v, qword k) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(k)); return r; }
static inline qword Offset(const qword *a, const qword *b) { return Sub(*a, *b); }
void func_001C8328(void *p, qword weights, qword a, qword b, float width, float scale)
{
    U w;
    int i;
    w.q = weights;
    for (i = 0; i < D_00475480.count; i++) {
        U x, y, z, k;
        struct M4 m;
        struct M4 *pm;
        qword d, n;
        float len;
        struct Obj *obj;
        if (w.f[i] == 0.0f)
            continue;
        obj = D_00475480.objs[i];
        d = Offset(&b, &a);
        n = Cross(Sub(a, ((struct M4 *(*)(void *))obj->vt[36].pfn)((char *)obj + obj->vt[36].d)->r[3].q), d);
        y.q = n;
        len = GetX(LenV(n));
        if (0.01f < len) {
            len = width / len;
            pm = &m;
            x.q = Normalize(Cross(n, d));
            k.q = Broadcast(len);
            n = Scale(n, k.q);
            y.q = n;
            k.q = Broadcast(0.01f);
            z.q = Scale(d, k.q);
            func_002BA818(&m.r[3].q, a);
            pm->r[0].q = x.q;
            pm->r[1].q = y.q;
            pm->r[2].q = z.q;
            m.r[0].f[3] = m.r[1].f[3] = m.r[2].f[3] = 0.0f;
            pm->r[3].f[3] = 1.0f;
            func_001C8248(p, func_001C8548(i), pm, scale, scale);
        }
    }
}
