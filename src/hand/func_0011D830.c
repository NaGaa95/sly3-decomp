// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef struct MATRIX4 { float mat[4][4]; } __attribute__((aligned(16))) MATRIX4;

MATRIX4 func_0011D768(void *pv);
MATRIX4 func_0011D558(MATRIX4 *pmatA, MATRIX4 *pmatB);

void func_0011D830(void *pv, MATRIX4 *pmat, MATRIX4 *pmatOut)
{
    MATRIX4 matRes;
    MATRIX4 matT;
    matT = func_0011D768(pv);
    matRes = func_0011D558(pmat, &matT);
    *pmatOut = matRes;
}
