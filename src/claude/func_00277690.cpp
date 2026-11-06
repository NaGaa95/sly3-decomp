// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_ASFIX: engine-divfix1
// Adapted from Sly 2 func_00224698 (face the linked object in the horizontal plane).
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct P { char pad[0x30]; qword pos; };
struct VTE { short d; short pad; P *(*pf)(void *); };
struct S { int a[3]; VTE *vt; char pad[0x130 - 0x10]; int k; char pad1[8]; int x13C; S *p140; };
extern "C" {
extern qword D_00317550, D_00317530, D_00317560;
extern char D_003291B0[], D_003291C0[];
void func_00243738(S *);
M3 func_0011CBF0(qword, qword);
void func_0011CCF8(void *, void *, M3 *);
void func_0023EFA0(S *, M3 *, void *, qword, void *);
}
static inline P *Pos(S *o) { return o->vt[36].pf((char *)o + o->vt[36].d); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Flatten(qword d, qword up)
{
    qword t, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(t), "=&j"(one) : "j"(d), "j"(up));
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(t) : "j"(up), "j"(t));
    return Sub(d, t);
}
static inline qword Len(qword d)
{
    qword len, one;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(len), "=&j"(one) : "j"(d));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(len) : "j"(len));
    return len;
}
static inline float X(qword v) { float f; int t; __asm__("qmfc2.ni %1,%2\n\tmtc1 %1,%0" : "=f"(f), "=&r"(t) : "j"(v)); return f; }
static inline qword DivQ(qword d, qword len)
{
    qword r;
    __asm__ __volatile__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(d), "0"(len));
    return r;
}
static inline qword NormalizeSafe(qword d, qword def)
{
    qword len = Len(d);
    if (X(len) < 0.0001f)
        return def;
    return DivQ(d, len);
}
extern "C" void func_00277690(S *p)
{
    M3 m;
    if (p->k == 0 || p->k == 4)
        return;
    func_00243738(p);
    if (p->x13C != 8)
        return;
    if (p->p140) {
        qword a = Pos(p->p140)->pos;
        qword d = Flatten(Sub(a, Pos(p)->pos), D_00317550);
        qword n = NormalizeSafe(d, D_00317530);
        m = func_0011CBF0(n, D_00317550);
    } else {
        func_0011CCF8(Pos(p), 0, &m);
    }
    func_0023EFA0(p, &m, D_003291B0, D_00317560, D_003291C0);
}
