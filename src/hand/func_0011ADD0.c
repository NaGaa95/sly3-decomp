// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef struct SL { void *pvFirst; void *pvLast; int ibNext; } SL;

void func_0011ADA8(SL *psl, void *pv);
void func_0011AD80(SL *psl, void *pv);

void func_0011ADD0(SL *psl, void *pvPrev, void *pv)
{
    if (pvPrev == 0) {
        func_0011ADA8(psl, pv);
    } else if (pvPrev == psl->pvLast) {
        func_0011AD80(psl, pv);
    } else {
        void **ppvPrev = (void **)((char *)pvPrev + psl->ibNext);
        *(void **)((char *)pv + psl->ibNext) = *ppvPrev;
        *ppvPrev = pv;
    }
}
