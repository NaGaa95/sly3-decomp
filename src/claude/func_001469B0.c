// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// A74: the length compare is one inline (FGt) so jump2 cross-jumps case 1 into case 0's tail; the float is read with a
// plain mtc1 asm (gcc emits the qmfc2 itself) - reorg cannot move `li v0,1` past that asm into the bc1t slot.
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; struct VTE e120; };
struct P { char pad[0xC]; struct VT *pvt; char pad1[0x198 - 0x10]; int x198; };
extern float D_0047A2A8;
extern float D_0047A2AC;
static __inline__ struct M4 *Matrix(struct P *p)
{
    struct VTE *e = &p->pvt->e120;
    return ((struct M4 *(*)(void *))e->pfn)((char *)p + e->d);
}
static __inline__ qword LenXY(qword d)
{
    __asm__("vmul.xy %0, %0, %0\n\tvaddy.x %0, %0, %0y" : "+j"(d));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    return d;
}
static __inline__ qword Len(qword d)
{
    qword t;
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    return d;
}
static __inline__ int FGt(qword l, float t)
{
    float g;
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
    return g > t;
}
int func_001469B0(struct P *p)
{
    switch (p->x198) {
    case 0:
        return FGt(LenXY(Matrix(p)->r[3]), D_0047A2AC);
    case 1:
        return FGt(Len(Matrix(p)->r[3]), D_0047A2A8);
    default:
        return 0;
    }
}
