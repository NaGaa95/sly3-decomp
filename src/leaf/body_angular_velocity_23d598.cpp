// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Angular velocity of the body's rotation frame (kind 6 chain element) in world space, zero vector otherwise. Based on
// Sly 2 func_001F4558: rate matrix of the chain turned by N * inverse(world) and the skew part packed into a quadword.
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
struct Frame { char pad[0x40]; MATRIX4 matWorld; };
struct FrameKind { char pad[0x94]; int kind; };
struct Body { char pad[0x4C]; Frame *frame; };
extern qword D_00317560;
extern "C" MATRIX3 func_0011C6F8(MATRIX3 *);
extern "C" void func_0011C798(MATRIX3 *);
extern "C" MATRIX4 func_0028BAD0(Frame *, Frame *);
extern "C" qword func_0023D598(Body *body)
{
    Frame *frame = body->frame;
    if (!frame || ((FrameKind *)frame)->kind != 6)
        return D_00317560;
    MATRIX3 matNorm;
    MATRIX3 matRate;
    MATRIX4 *pmatDmat = &func_0028BAD0(frame, 0);
    matRate = *(MATRIX3 *)pmatDmat;
    MATRIX3 *pmatWorld = (MATRIX3 *)&frame->matWorld;
    matNorm = *pmatWorld;
    func_0011C798(&matNorm);
    matRate = matNorm * func_0011C6F8(pmatWorld) * matRate;
    float gX = matRate.mat[1][2];
    float gY = matRate.mat[2][0];
    float gZ = matRate.mat[0][1];
    qword qwXYZ;
    int iTmp;
    __asm__("mfc1 %0, %2\n\tmfc1 %1, %3\n\tpextlw %0, %1, %0\n\tmfc1 %1, %4\n\tpcpyld %0, %1, %0"
            : "=&r"(qwXYZ), "=&r"(iTmp) : "f"(gX), "f"(gY), "f"(gZ));
    struct { float x, y, z, w; } __attribute__((aligned(16))) vecW;
    *(qword *)&vecW = qwXYZ;
    return *(qword *)&vecW;
}
