// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// func_0014AFB0: case 6 = matA/matB declared then assigned (3-store NRV copies), matC initialized, and a const M3 &mF0 bound before the inverse call (keeps &px->mF0 in s1).
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct X { char pad[0xB0]; M3 mB0; qword qE0; M3 mF0; qword q120; };
struct A0 { char pad[0x40]; M3 m40; };
struct O { char pad[0x94]; int x94; char pad1[0xA0 - 0x98]; A0 *pA0; };
struct P { int x0; void *p4; O *p8; char padC[0x1C - 0xC]; X *p1C; qword q20; };
extern "C" {
void func_0014B370(X *px);
qword func_0028E990(int n, A0 *pa, qword v);
void func_0028BFE8(void *p4, O *p8, qword v);
void func_0028C058(void *p4, O *p8, M3 *pm);
M3 func_0011C6F8(const M3 *pm);
void func_0011C798(M3 *pm);
M3 func_0011C9E8(qword v);
void func_0014AFB0(P *p);
}
struct VU_VECTOR4 { qword qw; };
inline M3 operator*(const M3 &matL, const M3 &matR) return mat
{
    qword qwL0 = matL.r[0];
    qword qwL1 = matL.r[1];
    qword qwL2 = matL.r[2];
    VU_VECTOR4 v0;
    VU_VECTOR4 v1;
    VU_VECTOR4 v2;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v0.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)&matR.r[0])->qw));
    *(VU_VECTOR4 *)&mat.r[0] = v0;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v1.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)&matR.r[1])->qw));
    *(VU_VECTOR4 *)&mat.r[1] = v1;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v2.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)&matR.r[2])->qw));
    *(VU_VECTOR4 *)&mat.r[2] = v2;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword Add(VU_VECTOR a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a.q), "j"(b)); return r; }

void func_0014AFB0(P *p)
{
    func_0014B370(p->p1C);
    switch (p->p8->x94) {
    case 1: {
        X *px = p->p1C;
        func_0028BFE8(p->p4, p->p8, Add(p->q20, func_0028E990(0, p->p8->pA0, Sub(px->q120, px->qE0))));
        break;
    }
    case 6: {
        X *px = p->p1C;
        M3 matA, matB;
        const M3 &mF0 = px->mF0;
        matA = mF0 * func_0011C6F8(&px->mB0);
        matB = func_0011C6F8(&p->p8->pA0->m40) * matA * p->p8->pA0->m40;
        func_0011C798(&matB);
        M3 matC = matB * func_0011C9E8(p->q20);
        func_0028C058(p->p4, p->p8, &matC);
        break;
    }
    }
}
