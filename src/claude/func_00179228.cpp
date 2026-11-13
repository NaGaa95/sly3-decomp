// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00179228: InsertPsysParticles (cf. Sly 2 func_0015B428). Sly 3 adds a func_00165B28 lookup (its matrix row 1
// replaces g_cm.dir in the facing test) and passes the PRG's k150 / &pblkFirst to the block allocator.
// Every pfr access goes through the &apd[i] pointer (apd[i - 43] = av[i], apd[i - 86] = apos[i]) so -Os keeps one giv.
typedef int qword __attribute__((mode(TI)));
struct EMITTER;
struct PD { unsigned int n0; int n4; float g8; float gC; };
struct PAIR { qword a; qword b; };
struct FR { qword apos[43]; qword av[43]; qword apd[43]; qword pad[3]; };
struct BLK {
    FR afr[2]; int x1080;
    int c; PAIR *apair; int pad108C; BLK *pblkNext;
};
struct PRG;
struct PRGVT { char pad[0x1B8]; short d; short pad2; void (*pfn)(PRG *, EMITTER *); };
struct PRG {
    char pad0[0xC]; PRGVT *pvt; char pad10[0x150 - 0x10]; int k160; char pad164[0x190 - 0x154]; int c1A0;
    char pad1A4[0x3A0 - 0x194]; int c3B0; char pad3B4[0x424 - 0x3A4]; int f434; int pad438; int k43C; int pad440;
    int c444; BLK *pblkFirst;
};
struct LM { float gMin, gMax; };
struct EMITTER { char pad[0xC8]; int fC8; char padCC[0xF0 - 0xCC]; int kF0; int fF4; LM lm; };
struct EMITX { PRG **ppprg; void *ppripg; EMITTER *pemitter; };
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct OVT { char pad[0x120]; VTE e120; };
struct OBJ { char pad[0xC]; OVT *pvt; };
static inline M4 *Matrix(OBJ *p) { VTE *e = &p->pvt->e120; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
extern "C" {
extern char D_00475480[];
OBJ *func_00165B28(void *pv);
PRG *func_00149638(void *pv);
void func_00149A08(PRG *pprg, EMITTER *p);
BLK *func_00149550(void *pv, int k, BLK **ppblk);
void *func_00292034(void *pv, int b, int cb);
int func_0011E8F0(int nMin, int nMax);
float func_0011E940(float gMin, float gMax);
void func_00179228(EMITTER *p, EMITX *px, int c, qword *apos, qword *av, float *ag1, float *ag2, qword *aa, qword *ab);
}

static inline float Dot(qword a, qword b)
{
    qword d, t;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(t) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}



void func_00179228(EMITTER *p, EMITX *px, int c, qword *apos, qword *av, float *ag1, float *ag2, qword *aa, qword *ab)
{
    PRG *pprg = 0;
    OBJ *pcm;
    if (px && px->ppprg)
        pprg = *px->ppprg;
    pcm = func_00165B28(D_00475480);
    if (!pcm)
        return;
    if (!pprg) {
        pprg = func_00149638(D_00475480);
        if (!pprg)
            return;
        if (px && px->ppprg)
            *px->ppprg = pprg;
        func_00149A08(pprg, p);
        if (px && px->pemitter)
            pprg->pvt->pfn((PRG *)((char *)pprg + pprg->pvt->d), px->pemitter);
        if (!pprg)
            return;
    }
    BLK *pblk = pprg->pblkFirst;
    int k = 0;
    while (k < c && (pblk || (pblk = func_00149550(D_00475480, pprg->k160, &pprg->pblkFirst)))) {
        qword *pq1 = pblk->afr[1].apos;
        for (unsigned int i = pblk->c; i < 43 && k < c; k++, i++) {
            FR *pfr = &pblk->afr[0];
#define pd ((PD *)&pfr->apd[i])
            ((qword *)pd)[-86] = apos[k];
            ((float *)&pfr->apos[i])[3] = ag1[k];
            ((qword *)pd)[-43] = av[k];
            ((float *)&((qword *)pd)[-43])[3] = ag2[k];
            func_00292034(pd, 0, sizeof(PD));
            pd->n0 = func_0011E8F0(0, pprg->c3B0 - 1);
            if (pprg->f434)
                pd->n0 &= ~1u;
            if (p->fC8)
                pd->n4 = func_0011E8F0(0, pprg->c1A0 - 1);
            if (pprg->k43C == 2) {
                pd->g8 = func_0011E940(p->lm.gMin, p->lm.gMax);
                if (!p->kF0 && 0.0f < Dot(Matrix(pcm)->r[1], ((qword *)pd)[-43]))
                    pd->g8 = -pd->g8;
                if (p->fF4)
                    pd->gC = func_0011E940(-3.14159265f, 3.14159265f);
            }
            if (pprg->k160 == 2) {
                PAIR *ppair = &pblk->apair[i];
                ppair->a = aa[k];
                ppair->b = ab[k];
            }
            pq1[i] = ((qword *)pd)[-86];
            pq1[i + 43] = ((qword *)pd)[-43];
            pq1[i + 86] = *(qword *)pd;
            pblk->c++;
            pprg->c444++;
        }
        pblk = pblk->pblkNext;
    }
}
