// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Re-pose a body on its attachment frame: func_001C9008 moves it by the frame's matrix and the offset `other`; an
// active body then gets the frame-relative velocity (the world rate matrix applied to the moved position, vt[40]) and
// the angular velocity (skew part of the rate matrix, vt[41]); without a frame both are zeroed.
// Same matrix helpers as body_angular_velocity_23d598.cpp (operator*, func_0011C798 normalise, func_0011C6F8 inverse).
#include "../P2/vector_intrinsics.h"
struct VU_VECTOR4 { qword qw; };
inline MATRIX3 operator*(const MATRIX3 &matL, const MATRIX3 &matR) return mat
{
    qword qwL0 = *(qword *)matL.mat[0];
    qword qwL1 = *(qword *)matL.mat[1];
    qword qwL2 = *(qword *)matL.mat[2];
    VU_VECTOR4 v0;
    VU_VECTOR4 v1;
    VU_VECTOR4 v2;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v0.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)matR.mat[0])->qw));
    *(VU_VECTOR4 *)mat.mat[0] = v0;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v1.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)matR.mat[1])->qw));
    *(VU_VECTOR4 *)mat.mat[1] = v1;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v2.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)matR.mat[2])->qw));
    *(VU_VECTOR4 *)mat.mat[2] = v2;
}
struct Method { short delta; short pad; void *fn; };
struct Frame { char pad[0x40]; MATRIX4 matWorld; };
struct Body { char pad00[0xC]; Method *vt; char pad10[0xC8]; int active; };
extern qword D_00317560;
extern "C" {
void func_001C9008(Body *, Frame *, MATRIX4 *);
MATRIX4 *func_0011D558(MATRIX4 *, MATRIX4 *, MATRIX4 *);
MATRIX4 func_0028BAD0(Frame *, Frame *);
MATRIX3 func_0011C6F8(MATRIX3 *);
void func_0011C798(MATRIX3 *);
}
static inline qword TransformPoint(const MATRIX4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(*(qword *)m.mat[0]), "j"(*(qword *)m.mat[1]), "j"(*(qword *)m.mat[2]), "j"(*(qword *)m.mat[3]), "j"(v));
    return r;
}
#define VCALL(o, n) ((void (*)(void *, qword))(o)->vt[n].fn)((char *)(o) + (o)->vt[n].delta,
extern "C" void func_0023DA68(Body *p, Frame *frame, MATRIX4 *other)
{
    MATRIX4 matOld;
    MATRIX4 matWorld;
    func_001C9008(p, frame, other);
    if (!p->active)
        return;
    if (!frame) {
        VCALL(p, 40) D_00317560);
        VCALL(p, 41) D_00317560);
        return;
    }
    {
        MATRIX4 matProd;
        func_0011D558(&matProd, &frame->matWorld, other);
        matOld = matProd;
    }
    {
        MATRIX4 matRet = func_0028BAD0(frame, (Frame *)0);
        matWorld = matRet;
    }
    VCALL(p, 40) TransformPoint(matWorld, *(qword *)matOld.mat[3]));
    MATRIX3 matNorm;
    struct { float x, y, z, w; } __attribute__((aligned(16))) vecW;
    MATRIX3 matRate;
    matNorm = *(MATRIX3 *)&matOld;
    func_0011C798(&matNorm);
    MATRIX3 *pmatWorld;
    matRate = matNorm * func_0011C6F8((MATRIX3 *)&matOld) * *(pmatWorld = (MATRIX3 *)&matWorld);
    // The method entry is read before the vector is built (the store of vecW stays behind both entry loads).
    Method *m = &p->vt[41];
    void *self = (char *)p + m->delta;
    void (*fn)(void *, qword) = (void (*)(void *, qword))m->fn;
    *(qword *)&vecW = PackVectorXYZ(matWorld.mat[1][2], matWorld.mat[2][0], matWorld.mat[0][1]);
    fn(self, *(qword *)&vecW);
}
