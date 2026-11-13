// CPP
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -malign-loops=3
// Copy a transform onto the body (func_001C9008) and, when the body is active, its velocities: zero vectors without
// a source frame, otherwise the linear velocity is the chain rate matrix (func_0028BAD0) applied to the new position and
// the angular velocity the skew part (m12, m20, m01) of the rate matrix, packed with pextlw/pcpyld (as in func_0023D598).
// HOW IT IS WRITTEN: mat/matRate declared first and assigned (one shared M4 return temp at sp+0x80, its address in s0);
// matNorm/matAng/vecW declared mid-body reuse the freed temp slots (matNorm 0x80, vecW 0xB0); matAng = product is an
// assignment (extra temp copy); R3() reference gives the `addiu v0,sp,0x40` row pointer; the vtable entry, adjusted
// this and function pointer are read into locals before the pack (puts the vtable load ahead of the asm in sched1).
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; M3(){} M3(const M3 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];} M3 &operator=(const M3 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;} };
struct M4 { U r[4]; M4(){} M4(const M4 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];r[3]=m.r[3];} M4 &operator=(const M4 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];r[3]=m.r[3];return *this;} };
struct XF { char pad[0x40]; M4 matWorld; };
struct VTE { short delta,pad; void (*fn)(void *, qword); };
struct P { char pad[0xC]; VTE *vt; char pad10[0xD8-0x10]; int active; };
extern qword D_00317560;
extern "C" void func_001C9008(P *, XF *, M4 *);
extern "C" M4 func_0011D558(const M4 *, const M4 *);
extern "C" M4 func_0028BAD0(XF *, XF *);
extern "C" M3 func_0011C6F8(const M3 *);
extern "C" void func_0011C798(M3 *);
static inline M3 operator*(const M3 &a,const M3 &b) return r
{
    qword a0=a.r[0].q,a1=a.r[1].q,a2=a.r[2].q;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[0].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[1].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[2].q));
}
static inline M3 &R3(M4 &m){return *(M3 *)&m;}
static inline qword Transform(const M4 &m,qword v) { qword r;
 __asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,vf0w":"=j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(m.r[3].q),"j"(v));return r;
}
extern "C" void func_0023DA68(P *p, XF *xf, M4 *transform)
{
    M4 mat;
    M4 matRate;
    func_001C9008(p, xf, transform);
    if (!p->active)
        return;
    if (!xf)
    {
        p->vt[40].fn((char *)p + p->vt[40].delta, D_00317560);
        p->vt[41].fn((char *)p + p->vt[41].delta, D_00317560);
        return;
    }
    mat = func_0011D558(&xf->matWorld, transform);
    matRate = func_0028BAD0(xf, 0);
    p->vt[40].fn((char *)p + p->vt[40].delta, Transform(matRate, mat.r[3].q));
    M3 matNorm = *(M3 *)&mat;
    func_0011C798(&matNorm);
    M3 matAng;
    matAng = matNorm * func_0011C6F8((M3 *)&mat) * R3(matRate);
    VTE *e = p->vt + 41;
    void *t = (char *)p + e->delta;
    void (*f)(void *, qword) = e->fn;
    float gX = matRate.r[1].f[2];
    float gY = matRate.r[2].f[0];
    float gZ = matRate.r[0].f[1];
    qword qwXYZ;
    int iTmp;
    __asm__("mfc1 %0, %2\n\tmfc1 %1, %3\n\tpextlw %0, %1, %0\n\tmfc1 %1, %4\n\tpcpyld %0, %1, %0"
            : "=&r"(qwXYZ), "=&r"(iTmp) : "f"(gX), "f"(gY), "f"(gZ));
    U vecW;
    vecW.q = qwXYZ;
    f(t, vecW.q);
}
