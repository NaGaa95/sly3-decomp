// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct DL {
    void *head;
    void *tail;
    int ibDle;
};
struct DLI {
    DL *m_pdl;
    void **m_ppv;
    int m_ibDle;
    DLI *m_pdliNext;
};
extern DLI *D_0036AE94;
struct DZ {
    int n0;
    int pad4[3];
    float g10;
    int pad14;
    int f18;
    int pad1C;
    DZ *pdzNext;
};
struct DZG {
    int pad0[3];
    DL dlC;
    int pad18[6];
    DL dl30;
    int c3C;
};
struct XP;
struct SO;
struct EmptyCleanup {
    char unused;
};
extern "C" void func_002BA690(void *, int);
extern "C" {
    XP *func_00175BA8(DZG *, DZ *);
    void func_00175968(DZG *, int, DZ *, XP *);
    void func_0011B028(DL *, void *);
    void func_0011AF60(DL *, void *);
    void func_0011B4B0(DZG *, DZ *);
}
static inline void InitDli(DLI *pdli, DL *pdl) {
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)pdl;
    pdli->m_ibDle = pdl->ibDle;
    pdli->m_pdliNext = D_0036AE94;
    D_0036AE94 = pdli;
}
static inline void *PvNextDli(DLI *pdli) {
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}
extern "C" void func_00175BD8(DZG *pdzg, int a, int b, XP **ppxp, int *pn, SO ***pppso) {
    DLI dli;
    DZ *pdz;
    InitDli(&dli, &pdzg->dl30);
    while ((pdz = (DZ *)PvNextDli(&dli)) != 0) {
        if (pdz->n0 == 1) {
            if (!pdz->f18) func_00175968(pdzg, a, pdz, func_00175BA8(pdzg, pdz));
            func_0011B028(&pdzg->dl30, pdz);
            func_0011AF60(&pdzg->dlC, pdz);
            pdzg->c3C++;
        }
    }
    func_0011B4B0(pdzg, 0);
    D_0036AE94 = dli.m_pdliNext;
    for (;;) {
        DZ *pdzBest = 0;
        float gMin = -0.01f;
        EmptyCleanup cleanup;
        for (DZ *pdzT = (DZ *)pdzg->dl30.head; pdzT; pdzT = pdzT->pdzNext) {
            if (pdzT->g10 < gMin) {
                gMin = pdzT->g10;
                pdzBest = pdzT;
            }
        }
        func_002BA690(&cleanup, 2);
        if (!pdzBest) break;
        if (!pdzBest->f18) func_00175968(pdzg, a, pdzBest, func_00175BA8(pdzg, pdzBest));
        func_0011B4B0(pdzg, pdzBest);
    }
}
