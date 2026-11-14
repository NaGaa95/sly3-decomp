// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// The destination pointers (pmAcc, pmProd) are taken before the first call so they live in
// s-regs as in the target (s6/s1), and loop 3 walks am itself (am++).
typedef int qword __attribute__((mode(TI)));
typedef union { qword r[4]; float f[4][4]; } M4;
M4 *func_0011D628(M4 *pm, const M4 *a);
M4 *func_0011D558(M4 *pm, const M4 *a, const M4 *b);
int func_0011D968(int c, int n, float *pgSrc, float *pgDst);

static inline void AddM4(M4 *pm, const M4 *a, const M4 *b)
{
    int i;
    for (i = 0; i < 4; i++) {
        qword r;
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a->r[i]), "j"(b->r[i]));
        pm->r[i] = r;
    }
}

void func_0014B808(int cb, M4 *am, M4 *amOut)
{
    M4 mSum;
    M4 mAcc;
    M4 mProd;
    M4 mT;
    int c;
    int i;
    c = cb / 4;
    for (i = 0; i < c; i++) {
        am[i].f[0][3] = 1.0f;
        am[i].f[1][3] = 1.0f;
        am[i].f[2][3] = 1.0f;
        am[i].f[3][3] = 1.0f;
    }
    {
        M4 *pmAcc = &mAcc;
        func_0011D628(&mProd, am);
        func_0011D558(pmAcc, am, &mProd);
    }
    mSum = mAcc;
    for (i = 1; i < c; i++) {
        func_0011D628(&mT, &am[i]);
        func_0011D558(&mProd, &am[i], &mT);
        AddM4(&mAcc, &mSum, &mProd);
        mSum = mAcc;
    }
    func_0011D968(4, 4, (float *)&mSum, (float *)&mAcc);
    for (i = 0; i < c; i++) {
        M4 *pmProd = &mProd;
        func_0011D628(&mT, am);
        func_0011D558(pmProd, &mT, &mAcc);
        amOut[i] = mProd;
        am++;
    }
}
