// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef struct SL { void *pvFirst; void *pvLast; int ibNext; } SL;

void func_0011ADA8(SL *psl, void *pv)
{
    void **ppvNext = (void **)((char *)pv + psl->ibNext);
    if (psl->pvFirst == 0) {
        psl->pvLast = pv;
        psl->pvFirst = pv;
    } else {
        *ppvNext = psl->pvFirst;
        psl->pvFirst = pv;
    }
}
