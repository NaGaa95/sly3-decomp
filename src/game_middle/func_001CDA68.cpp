// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Sweep vertices and create contacts from the first accepted segment hit (Sly 2 func_001A9D38 with the lazy version
// refresh of the vertex owner added): every vertex of A is moved into B's frame, the probe segment is traced against B, and
// the contact carries the smallest signed distance of A's probes (and of A's origin when flagged) along the hit normal.
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct LO { char pad0[0x40]; M4 m; char pad80[0x24]; int version; };
struct PROBES { int count; qword *points; };
struct A {
    LO *lo; int x4; float radius; int xC; int x10, x14; unsigned long flags; int first;
    char pad24[0xC]; M4 m; char pad70[0x1C]; qword *vertices; char pad90[0x10];
    PROBES probes; char padA8[0x18]; int version;
};
struct B {
    LO *lo; char pad4[0xC]; int x10, x14; unsigned long flags; char pad20[0x10]; M4 m; char pad70[0x48];
    int oldGeneration, generation;
};
struct HIT { qword p; char pad10[0x30]; float time; int x44, x48, tag; char pad50[0x10]; };
struct W; struct C;
extern "C" {
void func_0018B1E0(void *);
M4 func_0011D768(const M4 *);
int func_00164A10(B *, qword, qword, int, HIT *);
void func_001CB8B0(W *, A *, B *, qword, qword, int, int, int, C **, float);
}
static inline qword TransformNew(const M4 *m, qword p)
{
    qword r;
    __asm__("vmulax.xyz ACC,%1,%3x\n\tvmadday.xyz ACC,%2,%3y\n\tvmaddaz.xyz ACC,%4,%3z\n\tvmaddw.xyz %0,%5,$vf0w"
            : "=&j"(r) : "j"(m->r[0]), "j"(m->r[1]), "j"(p), "j"(m->r[2]), "j"(m->r[3]));
    return r;
}
static inline qword Transform(const M4 *m, qword p)
{
    __asm__("vmulax.xyz ACC,%1,%3x\n\tvmadday.xyz ACC,%2,%3y\n\tvmaddaz.xyz ACC,%4,%3z\n\tvmaddw.xyz %0,%5,$vf0w"
            : "=j"(p) : "j"(m->r[0]), "j"(m->r[1]), "0"(p), "j"(m->r[2]), "j"(m->r[3]));
    return p;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(d));
    return f;
}
static inline qword Normal(qword v)
{
    qword d, one, r;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(d) : "0"(d));
    __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q" : "=j"(r) : "j"(d), "j"(v));
    return r;
}
extern "C" void func_001CDA68(W *w, A *a, B *b, C **out)
{
    int i;
    PROBES *pr;
    if (a->version != a->lo->version)
        func_0018B1E0(a);
    pr = &a->probes;
    for (i = a->first; i < pr->count; i++) {
        HIT hits[2];
        qword pos = TransformNew(&a->m, a->vertices[i]);
        if (b->generation != b->oldGeneration)
            pos = Transform(&b->lo->m, Transform(&func_0011D768(&b->m), pos));
        qword dest = pr->points[i];
        int count = func_00164A10(b, pos, dest, 2, hits);
        if (count) {
            int skip = hits[0].time == 0.0f;
            if (skip < count) {
                qword dir = Normal(Sub(pos, dest));
                qword hit = hits[0].p;
                float g = 0.0f;
                int j;
                for (j = 0; j < pr->count; j++) {
                    float d = Dot(Sub(pr->points[j], hit), dir);
                    if (d < g)
                        g = d;
                }
                if (a->flags & 0x20000) {
                    float d = Dot(Sub(a->lo->m.r[3], hit), dir) - a->radius;
                    if (d < g)
                        g = d;
                }
                int kind = (b->flags & 0x20000) ? 9 : 8;
                int tag = (b->flags & 0x20000) ? 0 : hits[0].tag;
                func_001CB8B0(w, a, b, hit, dir, kind, tag, 0, out, g);
            }
        }
    }
}
