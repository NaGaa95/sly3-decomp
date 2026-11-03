// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Copies the particles of an input batch (position and velocity qwords plus their w components) into the emitter's chunk list,
// fills the per-particle record (random indices, random sweep and angle) and mirrors every record into the second frame.
// Based on Sly 2 func_0015B428; the nine parameters became an input struct and a scope object guards the allocations.
typedef int qword __attribute__((mode(TI)));
struct PD { unsigned int n0; int n4; float g8; float gC; };
struct PAIR { qword a; qword b; };
struct FR { qword apos[43]; qword av[43]; qword apd[43]; qword pad[3]; };
struct BLK {
    FR afr[2];
    int x1080;
    int c;
    PAIR *apair;
    int pad108C;
    BLK *pblkNext;
};
struct LMT { char pad0[4]; int c4; char pad8[0x214 - 8]; int f214; int c218; };
struct LM { float gMin, gMax; };
struct GRP {
    int k0;
    int f4;
    LM lm;
    char pad10[4];
    int f14;
    char pad18[8];
    LMT *plmt;
    int k24;
    int k28;
};
struct XF { char pad[0x1C]; GRP *pgrp; };
struct EM { char pad0[4]; XF *pxf; char pad8[0x50 - 8]; BLK *pblkFirst; char pad54[8]; int c5C; };
struct IN { int c; qword *apos; qword *av; float *ag1; float *ag2; };
struct PX { char pad[4]; qword *aa; qword *ab; };
struct VTE { short delta; short pad; qword *(*method)(void *); };
struct OBJ { char pad[0xC]; VTE *vt; };
extern "C" {
extern char D_00475480[];
void *func_001D2770(void *p);
void func_001D2798(void *p, int n);
PX *func_002020C8(EM *pem, IN *pin);
void func_00200328(EM *pem, PX *px);
OBJ *func_00165B28(void *p);
BLK *func_00149550(void *pv, int mode, void *plist);
void *func_00292034(void *pv, int b, unsigned int cb);
int func_0011E8F0(int nMin, int nMax);
float func_0011E940(float gMin, float gMax);
void func_00200C10(EM *pem, IN *pin);
}
// Stack scope with out-of-line constructor/release stubs (0x1D2770 / 0x1D2798)
struct SCOPE {
    char b;
    SCOPE() { func_001D2770(this); }
    ~SCOPE() { func_001D2798(this, 2); }
};

static inline qword Dot(qword a, qword b)
{
    qword d, t;
    // the second "j"(b) is allocation-only (VU numbering of the operands)
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(d), "=j"(t) : "j"(a), "j"(b), "j"(b));
    return d;
}
static inline float F3(qword q)
{
    float g;
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q), "j"(q));
    return g;
}

extern "C" void func_00200C10(EM *pem, IN *pin)
{
    SCOPE scope;
    GRP *pgrp = pem->pxf->pgrp;
    LMT *plmt = pgrp->plmt;
    PX *px = 0;
    if (pgrp->k28 == 2) {
        px = func_002020C8(pem, pin);
        func_00200328(pem, px);
    }
    BLK *pblk = pem->pblkFirst;
    OBJ *pobj = func_00165B28(D_00475480);
    int k = 0;
    while (k < pin->c && (pblk || (pblk = func_00149550(D_00475480, pgrp->k28, &pem->pblkFirst)))) {
        qword *pq1 = pblk->afr[1].apos;
        for (unsigned int i = pblk->c; i < 43 && k < pin->c; k++, i++) {
            qword *pa = pblk->afr[0].apos;
            pa[i] = pin->apos[k];
            ((float *)&pa[i])[3] = pin->ag1[k];
            pa[i + 43] = pin->av[k];
            ((float *)&pa[i + 43])[3] = pin->ag2[k];
#define pd ((PD *)&pa[i + 86])
            func_00292034(pd, 0, sizeof(PD));
            pd->n0 = func_0011E8F0(0, plmt->c218 - 1);
            if (plmt->f214)
                pd->n0 &= ~1u;
            if (pgrp->f14)
                pd->n4 = func_0011E8F0(0, plmt->c4 - 1);
            if (pgrp->k24 == 2) {
                pd->g8 = func_0011E940(pgrp->lm.gMin, pgrp->lm.gMax);
                if (!pgrp->k0 && pobj) {
                    VTE *e = &pobj->vt[36];
                    qword *pm = e->method((char *)pobj + e->delta);
                    if (0.0f < F3(Dot(pm[1], pa[i + 43])))
                        pd->g8 = -pd->g8;
                }
                if (pgrp->f4)
                    pd->gC = func_0011E940(-3.14159265f, 3.14159265f);
            }
            if (px) {
                PAIR *ppair = &pblk->apair[i];
                ppair->a = px->aa[k];
                ppair->b = px->ab[k];
            }
            pq1[i] = pa[i];
            pq1[i + 43] = pa[i + 43];
            pq1[i + 86] = *(qword *)pd;
            pblk->c++;
            pem->c5C++;
        }
        pblk = pblk->pblkNext;
    }
}
