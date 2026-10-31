// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=rj"(q) : "f"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } VU_VECTOR(float x, float y, float z); };
struct M4 { qword r[4]; };
struct LO;
struct LOV { char pad[0x120]; short d; short p; M4 *(*pfnMat)(void *, ...); char pad2[0x130 - 0x128]; short d130; short p130; qword (*pfn130)(void *, VU_FLOAT); };
struct LO { int a[3]; LOV *pvt; };
struct ST { char pad[0x10]; LO *pg; char pad14[0x40 - 0x14]; int k40; };
inline VU_VECTOR::VU_VECTOR(float x, float y, float z)
{
    qword t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
}
static inline qword MulAdd(VU_VECTOR a, VU_VECTOR b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(r) : "0"(a.q), "j"(s.q), "j"(b.q));
    return r;
}
extern "C" {
LO *func_00161720(ST *p);
LO *func_001F4A80(LO *p);
qword func_00167838(LO *p, VU_VECTOR v);
qword func_001619F8(ST *p);
}
qword func_001619F8(ST *p0)
{
    LO *pobj;
    ST *p = p0;
    pobj = func_00161720(p);
    if (pobj) {
        VU_VECTOR pos = pobj->pvt->pfnMat((char *)pobj + pobj->pvt->d)->r[3];
        VU_FLOAT s(0.25f);
        VU_VECTOR v = pobj->pvt->pfn130((char *)pobj + pobj->pvt->d130, s);
        return MulAdd(pos, v, s);
    } else if (!p->k40) {
        VU_VECTOR pos = p->pg->pvt->pfnMat((char *)p->pg + p->pg->pvt->d)->r[3];
        register LO *pg asm("$5") = p->pg;
        VU_FLOAT s(4000.0f);
        VU_VECTOR v = pg->pvt->pfnMat((char *)pg + pg->pvt->d, s)->r[0];
        return MulAdd(pos, v, s);
    } else {
        return func_00167838(func_001F4A80(p->pg), VU_VECTOR(0.0f, 0.0f, 4000.0f));
    }
}
