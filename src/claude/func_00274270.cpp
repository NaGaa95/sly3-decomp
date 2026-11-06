// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// ConvertZonePos (Sly 2 func_00221408 without the arc branch).
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M3 { qword r[3]; };
struct VTE { short d; short pad; M3 *(*pf)(void *); };
struct Z { int a[3]; VTE *vt; char pad[0x108 - 0x10]; void *curve; };
struct S { char pad[0x20]; Z *zone; char pad1[0xC8 - 0x24]; float time; };
extern "C" {
void func_0022E330(void *, float, qword *, qword *);
M3 func_0011CBF0(qword, qword);
qword func_001C9428(void *, void *, qword);
extern qword D_00317550;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Normalize(qword v)
{
    qword len, one, r;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(len), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(len) : "j"(len));
    __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "0"(len));
    return r;
}
static inline qword InverseRotate(const M3 &m, qword v)
{
    qword one, a, b, c;
    __asm__("vmul.xyzw %2,%5,%0\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\tvmul.xyzw %3,%6,%0\n\tvmul.xyzw %4,%7,%0\n\tvadday.x $ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\tvaddax.y $ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\tvaddax.z $ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y"
            : "+j"(v), "=&j"(one), "=&j"(a), "=&j"(b), "=&j"(c) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return v;
}
extern "C" void func_00274270(S *p, qword v, qword *out, qword *normal)
{
    U pos;
    M3 m;
    Z *z = p->zone;
    if (z->curve) {
        func_0022E330(z->curve, p->time, &pos.q, normal);
        m = func_0011CBF0(*normal, D_00317550);
        *out = InverseRotate(m, Sub(v, pos.q));
    } else {
        *normal = Normalize(z->vt[36].pf((char *)z + z->vt[36].d)->r[0]);
        *out = func_001C9428(0, p->zone, v);
    }
}
