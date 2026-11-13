// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
// Load the level body (Sly 3 version of Sly 2 LoadSwFromBrx, sly2-decomp src/hand/func_0013DA18.cpp): world-entry table
// (0x6C-byte WE records at psw+0x4630, count psw+0x462C) plus a per-entry chunk size table, the level sections, the
// stack allocations and two ZPRs, then per world entry its objects and their clones (entries with no clones are skipped).
// Callees by Sly 2 analogy: 0x119178/0x1191E0/0x1190A8 S16Read/S32Read/U32Read, 0x118DA0 Read, 0x118DC0 Align,
// 0x118DF0 Skip, 0x1D2538/0x1D2670/0x1D2470/0x1D25B0 alloc helpers (ALLOCREQ *), 0x1D2770/0x1D2798 CTX ctor/dtor,
// 0x1F9820/0x1F9860/0x1F9868 CLoadSpin begin/set name/end, 0x1A2C88/0x1A2D30 CBinaryInputStream ctor/dtor,
// 0x162A88 PchzFidName, 0x1507E0 PloCloneLo.
// Matching notes: the skipped entries read their size from acb[i] (loop.c makes the spilled pointer giv). fSkip is a
// stand-in: the game tests a register that is only ever set to 2 (reload materialises `li v1,2; beqz v1`), and setting
// it as its own statement after the ODD keeps the reload count (round-robin reload regs give &frameT v1).
struct BIS;
struct AREQ { int cb; int cbAlign; };
struct LO;
struct VTE { short d; short pad; void (*pfn)(); };
struct LO { int pad[3]; VTE *pvt; };
struct WE {
    int c0; LO **apo; int c8; int cC; int x10; int x14; void *pv18; char ab1C[0x40]; int x5C; int x60; int pad64[2];
};
struct SW {
    char pad0[0x3F00]; void *p3F00; int x3F04; void *p3F08; int x3F0C; void *p3F10; void *p3F14; int x3F18;
    char pad3F1C[0x3F48 - 0x3F1C]; char ab3F48[0x4348 - 0x3F48]; int x4348;
    char pad434C[0x462C - 0x434C]; int cwe; WE *awe; int pad4634; int iwe;
    char pad463C[0x4930 - 0x463C]; void *p4930;
};
struct GLOB { int x0, x4, x8, xC, x10, x14, x18, x1C; };
struct SPIN { int a[4]; };
struct LOL { int pad[2]; int c; LO **apo; };
class CTX {
    int storage[4];
public:
    CTX() __asm__("__3CTX");
    ~CTX() __asm__("_$_3CTX");
};
struct ZPR { char ab[0x630]; };
struct KEY { char ab[8]; int x8; char rest[0x110 - 12]; };
struct STREAM { unsigned char storage[0x70]; };
extern GLOB D_0036DBE0;
extern char D_003203F0[], D_00375290[], D_00474FF0[], D_00475480[], D_0036B118[];
extern int D_0047A488;
struct SPR { char pad[0x34]; unsigned int x34; };
extern SPR D_0036BC10;
extern "C" {
void func_0012CA40(void);
void func_0014FA38(SW *, BIS *);
int func_00119178(BIS *);
int func_001191E0(BIS *);
int func_001190A8(BIS *);
void func_00118DA0(BIS *, int, void *);
void func_00118DC0(BIS *, int);
void func_00118DF0(BIS *, int);
void *func_001D2538(AREQ *);
void *func_001D2670(AREQ *);
void *func_001D2470(AREQ *);
void *func_001D25B0(AREQ *);
void func_001F9820(SPIN *, int, int);
void func_001F9860(SPIN *, void *);
void func_001F9868(SPIN *);
void *func_00292034(void *, int, int);
void func_0021BFF8(void *, BIS *);
void func_0025B1B8(SW *);
void func_001CF640(void *, int);
void func_00246F58(void *, BIS *);
void func_0014FD20(SW *, BIS *);
void func_001519C8(void *, BIS *);
void func_001500F0(SW *, BIS *);
void func_0025EB00(SW *);
void func_0014FF58(SW *, BIS *);
void func_00249980(SW *);
void func_0025B6B8(SW *);
void func_00169398(SPR *);
void func_00196AA8(ZPR *, int, int);
void func_00236AE0(void);
void func_002340B8(SPR *, ZPR *);
void func_002BC568(KEY *);
void *func_00162A88(void *);
void func_001A2C88(STREAM *, int, void *, int);
void func_001A2D30(STREAM *, int);
void func_0025C930(int, BIS *);
void func_002499F0(SW *, int, BIS *);
void func_00234EA0(ZPR *, ZPR *, BIS *, void *);
void func_001ED7B0(SW *, BIS *);
void func_00151A38(LOL *);
void func_00151D80(int, BIS *, LOL *);
void func_00235DE0(void);
void func_001D2898(void *, void *, int);
LO *func_001507E0(LO *, int);
void func_00236B80(void);
void func_00247470(void *);
}
struct ODD { ODD(int n) { k.x8 = n; func_002BC568(&k); } KEY k; };
class OBJ {
public:
    OBJ(int k, void *pv, int n) __asm__("func_001A2C88");
    ~OBJ() { func_001A2D30(&s, 2); }
    STREAM s;
};

static inline void *AllocZ(AREQ *preq, int cb, int cbAlign) { preq->cb = cb; preq->cbAlign = cbAlign; return func_001D2538(preq); }
static inline void *AllocT(AREQ *preq, int cb, int cbAlign) { preq->cb = cb; preq->cbAlign = cbAlign; return func_001D2670(preq); }
static inline void *Alloc(AREQ *preq, int cb, int cbAlign) { preq->cb = cb; preq->cbAlign = cbAlign; return func_001D2470(preq); }
static inline void *AllocS(AREQ *preq, int cb, int cbAlign) { preq->cb = cb; preq->cbAlign = cbAlign; return func_001D25B0(preq); }

extern "C" void func_0014F440(SW *psw, BIS *pbis)
{
    SPIN h;
    union { AREQ req; struct { int pad[2]; int c; LO **apo; } lol; } u;
    int i;
    func_0012CA40();
    int prev = D_0036DBE0.x0;
    func_0014FA38(psw, pbis);
    int cur = D_0036DBE0.x0;
    psw->cwe = func_00119178(pbis);
    psw->awe = (WE *)AllocZ(&u.req, psw->cwe * 0x6C, 0x10);
    func_001F9820(&h, prev, cur);
    func_001F9860(&h, D_003203F0);
    int *acb = (int *)AllocT(&u.req, psw->cwe * 4, 0x10);
    int *pcb = acb;
    for (i = 0; i < psw->cwe; i++) {
        WE *pwe = &psw->awe[i];
        func_00118DA0(pbis, 0x40, pwe->ab1C);
        pwe->x5C = func_001191E0(pbis);
        pwe->x60 = func_001191E0(pbis);
        pwe->x10 = func_001191E0(pbis);
        pwe->x14 = func_001191E0(pbis);
        pwe->c8 = func_001191E0(pbis);
        *pcb++ = func_001190A8(pbis);
        pwe->pv18 = Alloc(&u.req, pwe->c8 * 4, 0x10);
        func_00292034(pwe->pv18, -1, pwe->c8 * 4);
    }
    func_0021BFF8(psw->ab3F48, pbis);
    func_0025B1B8(psw);
    func_001CF640(D_00375290, psw->x4348);
    func_00246F58(D_00474FF0, pbis);
    func_0014FD20(psw, pbis);
    func_001519C8(D_00475480, pbis);
    func_001500F0(psw, pbis);
    func_0025EB00(psw);
    func_0014FF58(psw, pbis);
    func_00118DC0(pbis, 0x10);
    func_00249980(psw);
    func_0025B6B8(psw);
    func_00169398(&D_0036BC10);
    if (D_0036DBE0.xC >> 1 & 1)
        D_0036BC10.x34 = 0x80000000;
    psw->p3F14 = psw->p3F10 = AllocS(&u.req, 0x10000, 0x10);
    psw->p3F00 = AllocS(&u.req, 0x7800, 0x10);
    psw->x3F04 = 0;
    psw->p3F08 = AllocS(&u.req, 0x6000, 0x10);
    psw->x3F0C = 0;
    CTX frame;
    ZPR zpr0;
    ZPR zpr1;
    psw->p4930 = &zpr0;
    func_00196AA8(&zpr0, D_0036DBE0.x1C * 3, 0x4000);
    func_00236AE0();
    func_00196AA8(&zpr1, D_0036DBE0.x1C * 2, D_0036DBE0.x1C * 3);
    func_002340B8(&D_0036BC10, &zpr0);
    int fSkip;
    for (i = 0; i < psw->cwe; i++) {
        WE *pwe = &psw->awe[i];
        if (!pwe->c8) {
            if (fSkip) func_00118DF0(pbis, acb[i]);
            continue;
        }
        ODD odd(2);
        fSkip = 2;
        char ab[0x4040];
        func_001F9860(&h, func_00162A88(pwe->ab1C));
        psw->iwe = pwe->x5C ? -1 : i;
        OBJ obj(0x403F, ab, 0);
        func_0025C930(1, pbis);
        D_0047A488 = func_001191E0(pbis);
        func_002499F0(psw, pwe->x10, pbis);
        func_00234EA0(&zpr0, &zpr1, pbis, D_0036B118);
        func_001ED7B0(psw, pbis);
        {
            CTX frameT;
            int j, k;
            LO **ppo;
            AREQ req2;
            func_00151A38((LOL *)&u.lol);
            func_00151D80(0, pbis, (LOL *)&u.lol);
            func_00118DC0(pbis, 0x10);
            func_00162A88(pwe->ab1C);
            func_00235DE0();
            psw->x3F18 = 0;
            pwe->c0 = u.lol.c;
            pwe->apo = (LO **)AllocZ(&req2, pwe->c0 * pwe->c8 * 4, 0x10);
            func_001D2898(pwe->apo, u.lol.apo, pwe->c0 * 4);
            ppo = &pwe->apo[pwe->c0];
            for (j = 1; j < pwe->c8; j++)
                for (k = 0; k < pwe->c0; k++)
                    *ppo++ = func_001507E0(pwe->apo[k], 0);
            if (pwe->x5C) {
                pwe->cC++;
            } else {
                for (k = 0; k < pwe->c8 * pwe->c0; k++) {
                    LO *po = pwe->apo[k];
                    ((void (*)(LO *))po->pvt[9].pfn)((LO *)((char *)po + po->pvt[9].d));
                }
            }
        }
    }
    func_00236B80();
    psw->p4930 = 0;
    psw->iwe = -2;
    func_00247470(D_00474FF0);
    func_001F9860(&h, 0);
    func_001F9868(&h);
}
