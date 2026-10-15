// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct SL { void *pvFirst; void *pvLast; int ibNext; };
struct SLI { SL *psl; void **ppv; int ibNext; SLI *psliNext; };
extern "C" SLI *g_psliFirst;

extern "C" void func_0011AE28(SL *psl, void *pv)
{
    void **ppvNext = (void **)((char *)pv + psl->ibNext);
    void **ppv = &psl->pvFirst;
    SLI *psli;
    while (pv != *ppv)
        ppv = (void **)((char *)*ppv + psl->ibNext);
    for (psli = g_psliFirst; psli; psli = psli->psliNext)
        if (psli->ppv == ppvNext)
            psli->ppv = ppv;
    *ppv = *ppvNext;
    if (psl->pvFirst == 0)
        psl->pvLast = 0;
    else if (*ppv == 0)
        psl->pvLast = (char *)ppv - psl->ibNext;
    *ppvNext = 0;
}

extern "C" int func_0011AEC8(SL *psl, void *pv);

extern "C" int func_0011B0C0(SL *pdl, void *pv);

struct SPLOTENTRY {
    int *an;
    int c;
    void (*pfn)(void *);
    void *pv;
    int i;
    int fRemove;
    SPLOTENTRY *next;
};
struct SPLOTLIST { SPLOTENTRY *first; SPLOTENTRY *last; int ibNext; float g; };

extern "C" void func_0011AD80(SPLOTLIST *p, SPLOTENTRY *n);
extern "C" void func_00163F28(SPLOTLIST *p);
extern "C" void *func_002459F8(int n);
extern "C" void func_00244F08(void *p, int n);
extern "C" float g_splotTime;

extern "C" void func_00163ED8(SPLOTLIST *p, SPLOTENTRY *n)
{
    int r = func_0011AEC8((SL *)p, n);
    if (r)
        return;
    func_0011AD80(p, n);
    n->i = 0;
}

static inline void InitSli(SLI *psli, SPLOTLIST *p)
{
    psli->psl = (SL *)p;
    psli->ppv = (void **)p;
    psli->ibNext = p->ibNext;
    psli->psliNext = g_psliFirst;
    g_psliFirst = psli;
}

static inline void *PvNextSli(SLI *psli)
{
    void *pv = *psli->ppv;
    psli->ppv = (void **)((char *)pv + psli->ibNext);
    return pv;
}

extern "C" void func_00164028(SPLOTLIST *p)
{
    SLI sli;
    SPLOTENTRY *n, *best;
    if (p->g == 0.0f)
        return;
    if (p->g <= g_splotTime)
    {
        InitSli(&sli, p);
        best = 0;
        while ((n = (SPLOTENTRY *)PvNextSli(&sli)) != 0)
        {
            if (n->fRemove)
            {
                func_0011AE28((SL *)p, n);
                n->i = 0;
                n->fRemove = 0;
            }
            else
            {
                int fReady = n->i >= n->c;
                if (fReady)
                    if (!best || best->c < n->c)
                        best = n;
            }
        }
        if (best)
        {
            func_00244F08(func_002459F8(0x34), 0);
            best->pfn(best->pv);
        }
        func_00163F28(p);
        p->g = 0.0f;
        g_psliFirst = sli.psliNext;
    }
}
