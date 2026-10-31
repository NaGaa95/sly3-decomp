// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0017D878: per-object transform loop (MulVec takes the matrix by value: its copy is the dead A0-C0 temp; v first in the asm operands)
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
union M4 { struct { qword r[4]; } q; M3 m3; float af[4][4]; };
union QF { float af[4]; qword q; };
struct LO;
struct LOV { char pad[0x120]; short d; short p; M4 *(*pfnMat)(LO *); };
struct LO { int a[3]; LOV *pvt; };
static inline M4 *VMat(LO *plo) { return plo->pvt->pfnMat((LO *)((char *)plo + plo->pvt->d)); }
struct PO { char pad[0x90]; M3 mat; char pad1[0xC0 - 0xC0]; qword pos; char pad2[0x118 - 0xD0]; float g118; };
struct W { char pad[0x3EB8]; int c; PO *apo[5]; qword q3ED0; };
struct S : LO { char pad[0x70 - 0x10]; char x70[0x104 - 0x70]; float g104; char pad1[0x10C - 0x108]; int n10C; };
struct SCALE { float x, y, z; };
static const QF s_vOff = { { -750.0f, 0.0f, 0.0f, 0.0f } };
extern "C" {
extern qword D_00317550;
extern W D_00475480;
M4 func_0011D768(M4 *pm);
M3 func_0011C8C0(qword v, float g);
float tanf(float g);
M4 func_0011D660(qword pos, M3 *pm, SCALE *pscale);
M4 func_0011D558(M4 *pa, M4 *pb);
void func_0018E800(void *p, qword q, M4 *pm, int n, float g0, float g1);
void func_0017D878(S *p);
}
static inline M3 Mul(const M3 &a, const M3 &b) return r
{
    qword a0 = a.r[0], a1 = a.r[1], a2 = a.r[2], x0, x1, x2;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(x0) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[0]));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(x1) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[1]));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(x2) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[2]));
    r.r[0] = x0; r.r[1] = x1; r.r[2] = x2;
}
static inline qword MulVec(M3 m, qword v)
{
    qword r;
    __asm__("vmulax.xyz ACC,%2,%1x\n\tvmadday.xyz ACC,%3,%1y\n\tvmaddz.xyz %0,%4,%1z"
        : "=j"(r) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return r;
}
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
void func_0017D878(S *p)
{
    M4 mInv = func_0011D768(VMat(p));
    M3 mRot = func_0011C8C0(D_00317550, 3.14159265f);
    for (int i = 0; i < D_00475480.c; i++) {
        PO *po = D_00475480.apo[i];
        M3 mNew = Mul(po->mat, mRot);
        qword mv = MulVec(mNew, s_vOff.q);
        QF pos;
        pos.q = Add(po->pos, mv);
        float g = tanf(po->g118 * 0.5f) * 1.83f;
        SCALE scale;
        scale.x = 1.0f;
        scale.y = g;
        scale.z = g;
        M4 m = func_0011D660(pos.q, &mNew, &scale);
        m = func_0011D558(&m, &mInv);
        func_0018E800(p->x70, D_00475480.q3ED0, &m, p->n10C, p->g104, p->g104);
    }
}
