// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct XP;
struct SOPART;
struct SO;
struct LINK { XP *pxpFirst; LINK *plinkNext; XP **ppxpOut; SO *pso; };
struct ATT { char pad0[0x34]; SOPART *psopart; char pad38[0x60 - 0x38]; SO *pso; LINK *plinkFirst; XP *pxpFirst; };
struct SO { char pad0[0xDC]; ATT *patt; char padE0[0x288 - 0xE0]; SOPART *psopart; char pad28C[0x2E8 - 0x28C]; SO *psoTarget; };
extern char D_00475480[];
extern qword D_00317550;
extern "C" {
M3 func_0011CBF0(qword, qword);
void func_001CB8B0(void *, SOPART *, SOPART *, qword, qword, float, int, void *, void *, XP **);
}
static inline qword Sub(const qword &a, const qword &b) {
    qword r;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
// Transform v into the frame of m (one dot product per row); rows 1 and 2 are loaded by the asm itself.
// The row products and the (1,1,1) vector live in fixed VU registers (vf4, vf7-vf9), as in the target.
static inline qword Rotate(const M3 &m, qword v) {
    qword r;
    qword m0 = m.r[0];
    __asm__("lqc2 $vf2,0x20(%3)\n\tlqc2 $vf1,0x10(%3)\n\tvmul.xyzw $vf7,%1,%2\n\tvmaxw.xyzw $vf4,$vf0,$vf0w\n\tvmul.xyzw $vf8,$vf1,%2\n\tvmul.xyzw $vf9,$vf2,%2\n\tvadday.x $ACC,$vf7,$vf7y\n\tvmaddz.x %0,$vf4,$vf7z\n\tvaddax.y $ACC,$vf8,$vf8x\n\tvmaddz.y %0,$vf4,$vf8z\n\tvaddax.z $ACC,$vf9,$vf9x\n\tvmaddy.z %0,$vf4,$vf9y"
        : "=&j"(r) : "j"(m0), "j"(v), "r"(&m) : "vf1", "vf2", "vf4", "vf7", "vf8", "vf9");
    return r;
}
static inline float X(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline float Y(qword q) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(q)); return f; }
static inline float Z(qword q) { float f; __asm__("pextuw %0,$zero,%1" : "=r"(f) : "r"(q)); return f; }
extern "C" void func_0024F470(SO *pso, int grf, void *plo, qword posOther, qword direction, qword pos)
{
    XP **ppxpFirst, **ppxpOut;
    SOPART *psopartOther;
    SO *psoTarget = pso->psoTarget;
    ATT *patt;
    if (psoTarget && (patt = psoTarget->patt) != 0) {
        SO *psoOwner = patt->pso;
        ATT *pattThis = pso->patt;
        LINK *plink = pattThis->plinkFirst;
        while (plink && plink->pso != psoOwner) plink = plink->plinkNext;
        if (plink) {
            ppxpFirst = &plink->pxpFirst;
            ppxpOut = plink->ppxpOut;
            psopartOther = psoOwner->patt->psopart;
        } else {
            psopartOther = 0;
            ppxpFirst = ppxpOut = &pattThis->pxpFirst;
        }
    } else {
        psopartOther = 0;
        ppxpFirst = ppxpOut = &pso->patt->pxpFirst;
    }
    M3 mat = func_0011CBF0(direction, D_00317550);
    qword d = Sub(pos, posOther);
    __asm__("" : "=j"(d) : "0"(d));   // tie: gives the vsub a dependent so it issues before the m0 load
    qword posLocal = Rotate(mat, d);
    if ((grf & 1) || ((grf & 8) && X(posLocal) < 0.0001f))
        func_001CB8B0(D_00475480, pso->psopart, psopartOther, pos, mat.r[0], X(posLocal), (grf & 1) ? 11 : 10, 0, 0, ppxpFirst);
    if ((grf & 2) || ((grf & 0x10) && Y(posLocal) < 0.0001f))
        func_001CB8B0(D_00475480, pso->psopart, psopartOther, pos, mat.r[1], Y(posLocal), (grf & 2) ? 11 : 10, 0, 0, ppxpFirst);
    if ((grf & 4) || ((grf & 0x20) && Z(posLocal) < 0.0001f))
        func_001CB8B0(D_00475480, pso->psopart, psopartOther, pos, mat.r[2], Z(posLocal), (grf & 4) ? 11 : 14, 0, 0, ppxpFirst);
    *ppxpOut = *ppxpFirst;
}
