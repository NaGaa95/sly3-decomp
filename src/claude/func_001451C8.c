// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001451C8 (written from the target): contact-pair pass (push / hit reactions through func_00240CB0,
// stops at the first reaction), then for flag 0x2F bit 0 the shape-vs-shape query of p358 (frame scope + PvAllocSlot
// node buffer), the 8/9 vtable notifications of the 0x330/0x344 lists and the post-hit sound. Keys: all address-taken
// locals declared first (vHit union 0x10, ctx 0x20, req 0x30, then the ints); 'f = x < -0.7f' store-flag;
// '!x198' arm before the x198 arm and 'if (x424) {...} else a40 = fHit;' so both a40 copies cross-jump; NMin clamp;
// Alloc() inline storing cb/cbAlign through the request pointer; 'c50 = cMax; pent = aent; pentFirst = aent;';
// 'pent = &D_00341E00; pentFirst = pent;'; the other half recomputed as '((1 - iOther) << 6) + (int)pct'.
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct AREQ { int cb; int cbAlign; };
struct CTX { int a[4]; };
struct ENT { int a[3]; };
struct SH {
    struct SHP *pso; char pad4[0x18 - 4]; unsigned long grf; char pad20[0x70 - 0x20]; struct SH *pnext;
    char pad74[0x7C - 0x74]; int c7C; char pad80[0x84 - 0x80]; int x84; char pad88[0xC0 - 0x88]; int xC0;
};
struct SHP { char pad[0xA4]; int xA4; };
struct DC { char pad[0x20]; qword v20; float g30; struct SH *pshFirst; char pad38[0x64 - 0x38]; struct LNK *plnk; };
struct HALF { char pad[8]; struct P *po; char padC[0x10 - 0xC]; qword v10; char pad20[0x30 - 0x20]; qword v30; };
struct CT { char pad[0x80]; qword v80; char pad90[0xAC - 0x90]; struct CT *pnext; };
struct LNK { struct CT *pct; struct LNK *pnext; };
struct OBJ { char pad[0xC]; struct VTE *pvt; };
struct P {
    char pad0[0xC]; struct VTE *pvt; char pad10[0x2F - 0x10]; unsigned long b2F : 8; char pad30[0xDC - 0x30];
    struct DC *pdc; char padE0[0x130 - 0xE0]; int x130; char pad134[0x190 - 0x134]; int x190; int pad194; int x198;
    char pad19C[0x1F8 - 0x19C]; int x1F8; char pad1FC[0x208 - 0x1FC]; int x208; char pad20C[0x2B0 - 0x20C]; int x2B0;
    char pad2B4[0x320 - 0x2B4]; struct OBJ *po320; float g324; void *p328; int c32C; struct OBJ *apo330[4]; int c340;
    struct OBJ *apo344[3]; float g350; float g354; struct P *p358; float g35C; char pad360[0x424 - 0x360]; int x424;
    struct P *p428;
};
extern struct CLOCK { float t; float dt; } g_clock;
extern qword D_00317560;
extern struct ENT D_00341E00;
extern char D_0036E740[][0x11C0];
extern char D_00475480[];
int func_0013B500(void *object, int kind);
qword func_00120D98(qword first, qword second);
void func_001459D0(struct P *p, struct P *po, int *pa, int *pb);
void func_00240CB0(void *self, int a, void *target, int b, int c, int d, qword e, qword f, int g);
void *func_001D2770(void *receiver);
void func_001D2798(void *receiver, int flags);
void *PvAllocSlot(struct AREQ *preq) __asm__("PvAllocSlot__FP8ALLOCREQ");
void func_0018B1E0(struct SH *p);
int func_00119C20(int n, int m, qword v, int *pc, struct ENT **ppent, float g);
void func_001CC790(void *pool, struct SH *a, struct SH *b, int c, struct ENT *pent, struct ENT *pentLast, int *pn);
void func_001CBAA0(void *game, int n);
void *func_001FE728(void *receiver, int flags);
void func_001A9058(void *p, int n, float g);
void func_001451C8(struct P *p);
typedef void (*PFNV)(void *);
typedef void (*PFNQ)(void *, qword);
typedef qword (*PFNR)(void *);
#define VCALL(po, i) { struct OBJ *_po = (struct OBJ *)(po); struct VTE *_e = &_po->pvt[i]; ((PFNV)_e->pfn)((char *)_po + _e->d); }
static inline void *Alloc(struct AREQ *preq, int cb) { preq->cb = cb; preq->cbAlign = 0x10; return PvAllocSlot(preq); }
static inline int NMin(int a, int b) { return a < b ? a : b; }
static inline float GetX(qword v) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(v)); return f; }
static inline float Len(qword v)
{
    qword d, one; float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}

void func_001451C8(struct P *p)
{
    union { qword q; float f[4]; } vHit;
    struct CTX ctx;
    struct AREQ req;
    int a40, a44, a48, a4C, c50;
    struct ENT *pent;
    int n58;
    int fHit;
    int fPush;
    struct LNK *plnk;
    struct CT *pct;
    int fAlloc;
    int i;
    fHit = 0;
    p->p428 = 0;
    fPush = 0;
    for (plnk = p->pdc->plnk; plnk; plnk = plnk->pnext) {
        for (pct = plnk->pct; pct; pct = pct->pnext) {
            int iOther = (struct P *)((struct HALF *)pct)->po != p;
            struct HALF *ph = (struct HALF *)((char *)pct + (iOther << 6));
            struct HALF *pho = (struct HALF *)((char *)pct + ((1 - iOther) << 6));
            struct P *po = pho->po;
            int f;
            if (func_0013B500(po, 0x59))
                continue;
            f = GetX(func_00120D98(ph->v30, pct->v80)) < -0.7f;
            p->p428 = po;
            fHit = 1;
            vHit.q = ph->v10;
            a40 = 0;
            a44 = 0;
            if (func_0013B500(po, 0x52)) {
                fPush = 1;
                if (p < po) {
                    a48 = 0;
                    a4C = 0;
                    func_001459D0(p, po, &a40, &a44);
                    f = 0;
                    func_001459D0(po, p, &a48, &a4C);
                    if (a40 == 0)
                        f = a48 ? 0 : fPush;
                    if (a48 || a4C > 0) {
                        po->p428 = p;
                        func_00240CB0(f ? po : p, 0, po, 0x200, a4C, a48, ph->v10, pho->v30, 0);
                        po->p428 = 0;
                    }
                }
            } else if (!p->x198) {
                if (f) {
                    if (p->x208)
                        a44 = p->x1F8;
                    else
                        a40 = fHit;
                }
            } else if (p->x190 == fHit) {
                if (p->x424) {
                    if (f && p->x2B0 != 4)
                        a44 = p->x1F8;
                } else
                    a40 = fHit;
            }
            if (a40 || a44 > 0) {
                func_00240CB0(f ? p : po, 0, p, 0x200, a44, a40, ((struct HALF *)(((1 - iOther) << 6) + (int)pct))->v10, ph->v30, 0);
                goto done;
            }
        }
    }
done:
    p->p428 = 0;
    if (!(p->b2F & 1))
        return;
    fAlloc = 0;
    if (p->p358) {
        struct SH *psh;
        int cMax = 0;
        struct ENT *aent;
        for (psh = p->p358->pdc->pshFirst; psh; psh = psh->pnext)
            if (!(psh->c7C < cMax))
                cMax = psh->c7C;
        func_001D2770(&ctx);
        cMax = NMin(cMax, 0x1555);
        aent = (struct ENT *)Alloc(&req, cMax * 12);
        n58 = 0;
        for (psh = p->p358->pdc->pshFirst; psh; psh = psh->pnext) {
            struct ENT *pentFirst;
            int r;
            int c;
            struct SH *psh2;
            if (psh->grf & 0x20000)
                continue;
            c50 = cMax;
            pent = aent;
            pentFirst = aent;
            if (psh->xC0 != psh->pso->xA4)
                func_0018B1E0(psh);
            r = func_00119C20(psh->x84, 0x7FFFFFFF, p->pdc->v20, &c50, &pent, p->pdc->g30);
            if (r == 1)
                continue;
            if (r == 0) {
                c = 0;
                pent = &D_00341E00;
                pentFirst = pent;
            } else {
                c = pent - pentFirst;
                pent--;
            }
            for (psh2 = p->pdc->pshFirst; psh2; psh2 = psh2->pnext) {
                if (psh2->grf & 0x20000)
                    continue;
                func_001CC790(D_00475480, psh2, psh, c, pentFirst, pent, &n58);
            }
        }
        if (n58) {
            fAlloc = 1;
            func_001CBAA0(D_00475480, n58);
        }
        func_001D2798(&ctx, 2);
    }
    if (fAlloc) {
        for (i = 0; i < p->c340; i++)
            VCALL(p->apo344[i], 9);
        if (p->p328 && 1.0f < g_clock.t - p->g35C)
            func_001FE728(p->p328, 1);
        for (i = 0; i < p->c32C; i++)
            VCALL(p->apo330[i], 8);
        p->g35C = g_clock.t;
    } else {
        for (i = 0; i < p->c32C; i++)
            VCALL(p->apo330[i], 9);
        if (g_clock.t - p->g35C < p->g354) {
            for (i = 0; i < p->c340; i++)
                VCALL(p->apo344[i], 8);
        } else {
            for (i = 0; i < p->c340; i++)
                VCALL(p->apo344[i], 9);
        }
    }
    if (fHit && !fAlloc) {
        if (p->po320) {
            VCALL(p->po320, 8);
            { struct OBJ *po = p->po320; struct VTE *e = &po->pvt[34]; ((PFNQ)e->pfn)((char *)po + e->d, vHit.q); }
        }
    } else if (p->po320) {
        VCALL(p->po320, 9);
    }
    if (!fHit)
        return;
    if (p->x198)
        return;
    {
        int f = 0;
        struct VTE *e = &p->pvt[38];
        if (Len(((PFNR)e->pfn)((char *)p + e->d)) < 750.0f)
            f = fPush ^ 1;
        if (f) {
            int g = 0;
            if (!p->x198)
                g = p->x208 != 0;
            if (g)
                func_00240CB0(p, 0, p, 0x200, p->x1F8, 0, vHit.q, D_00317560, 0);
            else
                func_00240CB0(p, 0, p, 0x200, 0, 1, D_00317560, D_00317560, 0);
        } else if (!fAlloc) {
            if (p->x130 != -1 && 0.2f < g_clock.t - p->g324) {
                func_001A9058(D_0036E740[p->x130], 1, 0.2f);
                p->g324 = g_clock.t;
            }
        }
    }
}
