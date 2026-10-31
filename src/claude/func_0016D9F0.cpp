// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0016D9F0: heading from the target to the actor (flattened against Z), then the request's point/direction
// offsets along it. Sly 2 counterpart: func_0017AA78.
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(const int *)&f)); }
    VU_FLOAT(int, float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct M4 { qword r[4]; };
struct LO;
struct LOV { char pad[0x120]; short d; short p; M4 *(*pfnMat)(LO *); };
struct LO { int a[3]; LOV *pvt; };
struct P { char pad0[0x10]; LO *pactor; char pad14[0x5C - 0x14]; LO *ptarget; };
struct REQ { int flag; float along, up; int padC; qword point, direction; };
extern "C" {
extern qword D_00317530, D_00317550;
void func_0016D9F0(P *p, REQ *preq, qword *ppoint, qword *pdirection);
}
static inline M4 *VMat(LO *plo) { return plo->pvt->pfnMat((LO *)((char *)plo + plo->pvt->d)); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Reject(qword a, qword n)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(a), "j"(n));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(d) : "j"(n), "j"(d));
    return Sub(a, d);
}
static inline qword Normal(qword a, qword fallback)
{
    qword d;
    qword one;
    float len;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(len) : "j"(d));
    if (len < 0.0001f) {
        __asm__("" : : "j"(one), "j"(one), "j"(one)); /* zero-instruction: makes one global (priority above a) so global-alloc puts d in vf1 */
        d = fallback;
    }
    else
        __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(d) : "j"(d), "j"(a));
    return d;
}
static inline qword AddScaled2(qword p, qword a, VU_FLOAT sa, qword b, VU_FLOAT sb)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %2, %3x\n\tvmaddx.xyzw %0, %4, %5x" : "=j"(r) : "j"(p), "j"(a), "j"(sa.q), "j"(b), "j"(sb.q));
    return r;
}
static inline qword AddScaled(qword p, qword b, VU_FLOAT sb)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(p), "j"(b), "j"(sb.q));
    return r;
}
void func_0016D9F0(P *p, REQ *preq, qword *ppoint, qword *pdirection)
{
    qword pos = VMat(p->pactor)->r[3];
    qword dir = Normal(Reject(Sub(pos, VMat(p->ptarget)->r[3]), D_00317550), D_00317530);
    qword n;
    { register const qword *pn __asm__("$2") = &D_00317550; n = *pn; } /* register pin: &D_00317550 in v0 like the target */
    qword point = AddScaled2(preq->point, dir, VU_FLOAT(preq->along), n, VU_FLOAT(preq->up));
    qword direction = AddScaled(preq->direction, n, VU_FLOAT(0, -1500.0f));
    *ppoint = point;
    *pdirection = direction;
}
