// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0028B640: DmatSkew - Sly 2 DmatSkew__FP7MATRIX4P7VECTOR4PvG9VU_VECTOR (0x22CCD0) rewritten without asm/pins:
// skew matrix of v (lane helpers mtc1/prot3w/pextuw) times *pmat via the NRV MATRIX3 operator*, w lanes cleared.
typedef int qword __attribute__((mode(TI)));
struct MATRIX3 { float mat[3][4]; } __attribute__((aligned(16)));
struct VU_VECTOR4 { qword qw; };
inline MATRIX3 operator-(const MATRIX3 &a, const MATRIX3 &b) return r
{
    for (int i = 0; i < 3; i++) {
        qword q;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(q) : "j"(*(qword *)a.mat[i]), "j"(*(qword *)b.mat[i]));
        *(qword *)r.mat[i] = q;
    }
}
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
struct MATRIX4 { float mat[4][4]; } __attribute__((aligned(16)));
static inline float GX(qword q) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q)); return f; }
static inline float GY(qword q) { float f; __asm__("prot3w %0, %1" : "=r"(f) : "r"(q)); return f; }
static inline float GZ(qword q) { float f; __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q)); return f; }
extern "C" void *memset(void *, int, unsigned int);
extern "C" MATRIX4 *func_0028B640(MATRIX4 *pdmat, void *pv, MATRIX3 *pmat, qword v)
{
    memset(pdmat, 0, sizeof(MATRIX4));
    float x = GX(v);
    float y = GY(v);
    float z = GZ(v);
    pdmat->mat[0][1] = z;
    pdmat->mat[0][2] = -y;
    pdmat->mat[1][0] = -z;
    pdmat->mat[1][2] = x;
    pdmat->mat[2][0] = y;
    pdmat->mat[2][1] = -x;
    *(MATRIX3 *)pdmat = *(MATRIX3 *)pdmat * *pmat;
    pdmat->mat[2][3] = 0.0f;
    pdmat->mat[1][3] = 0.0f;
    pdmat->mat[0][3] = 0.0f;
    return pdmat;
}
