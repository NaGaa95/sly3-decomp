// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef struct DL { void *pvFirst; void *pvLast; int ibDle; } DL;
typedef struct DLE { void *pvNext; void *pvPrev; } DLE;
typedef struct DLI { DL *pdl; void **ppv; int ibDle; struct DLI *pdliNext; } DLI;
#define PDLE(pdl, pv) ((DLE *)((char *)(pv) + (pdl)->ibDle))

void func_0011AF60(DL *pdl, void *pv)
{
    DLE *pdle = PDLE(pdl, pv);
    if (!pdl->pvLast) {
        pdl->pvLast = pv;
        pdl->pvFirst = pv;
    } else {
        DLE *pdleLast = PDLE(pdl, pdl->pvLast);
        pdle->pvPrev = pdl->pvLast;
        pdleLast->pvNext = pv;
        pdl->pvLast = pv;
    }
}
