// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00136908: adapted from the matched Sly 2 source src/hand/func_0012F9B8.cpp (Sly 3 offsets, calls and the new tests).
struct VTE { short d; short pad; void (*pfn)(); };
struct POLY { float a, b, c; };
struct E50 { unsigned int k; int x4; };
struct E58 { int x0; int x4; int x8; };
struct EV { int a[5]; };
struct DL { void *pvFirst; void *pvLast; int ibDle; };
struct T {
    int x0; char pad4[0x40 - 4]; struct DL dl40; int c4C; struct E50 *ae50; int c54; struct E58 *ae58; int x5C;
    int x60; float g64; float g68; int pad6C; struct POLY poly; int pad7C; float g80; float g84; int cev; struct EV *aev; int x90;
};
struct B98 { char pad[0x98]; short s98; };
struct N34 { int x0; int x4; struct B98 *x8; int xC; int x10; int x14; VTE *pvt; int x1C; int x20; struct P *p24; struct N34 *pnNext; };
struct N38 { int x0; int x4; int x8; int xC; struct N38 *pnNext; };
struct P {
    int x0; int x4; int x8; VTE *pvt; int x10; struct T *pt; int x18; float g1C; float g20; char pad24[0x34 - 0x24];
    struct N34 *pn34; struct N38 *pn38; int x3C; float g40; int x44; float g48; float g4C; int x50; int pad54[2]; int x5C;
};
struct G { P *p; G(P *pp) : p(pp) { ((void (*)(P *))p->pvt[1].pfn)((P *)((char *)p + p->pvt[1].d)); }
    ~G() { ((void (*)(P *))p->pvt[2].pfn)((P *)((char *)p + p->pvt[2].d)); } };
struct CLOCK { float t; };
extern "C" {
extern char D_004799A0[];
extern char D_00479994[];
extern VTE D_00351CE8[];
extern char D_0036BD20[];
extern struct CLOCK g_clock;
P *PvAlloc__9POOLSTATE(void *);
void *memset(void *, int, unsigned int);
void func_002BBE90(P *);
float func_00171C98(void *);
void func_00138B68(P *, float);
void func_0011AF60(void *, void *);
void __as__12EvalFrameRefP9EvalFrame(P *, int);
void func_00136E28(struct T *, int, struct E50 *, int *, struct B98 **);
void func_00241F00(int, long);
void *func_0014BE38(unsigned int);
void func_002BBC38(struct N34 *);
void func_0028ECE0(int, struct B98 *, void *);
void func_00136FC8(struct T *, int, struct E58 *, int *, int *);
void *func_0012F240(unsigned int);
void func_00138AF0(P *, int);
void func_00138270(P *, struct EV *);
void func_0028F978(P *, int);
void func_001380E0(P *);
void func_00137EA0(P *);
float *func_00136880(struct T *, int);
void func_00138BF8(P *, float);
}
static inline float GClamp(float g, float lo, float hi) { float r; if (g < lo) r = lo; else if (hi < g) r = hi; else r = g; return r; }
static inline float GEval(struct POLY *pp, float t) { return pp->a + t * (pp->b + t * pp->c); }

extern "C" void func_00136908(struct T *pt, int x, int grf, P **pp, float g0, float g1)
{
    P *p = PvAlloc__9POOLSTATE(D_004799A0);
    int i, j, k;
    memset(p, 0, 0x60);
    func_002BBE90(p);
    p->pt = pt;
    p->x18 = x;
    p->g1C = g0;
    p->x3C = grf;
    p->g48 = pt->g68;
    {
        p->g4C = GClamp(GEval(&pt->poly, func_00171C98(D_0036BD20)), pt->g80, pt->g84);
    }
    func_00138B68(p, g1);
    func_0011AF60(D_00479994, p);
    func_0011AF60(&pt->dl40, p);
    ((void (*)(P *))p->pvt[1].pfn)((P *)((char *)p + p->pvt[1].d));
    G g(p);
    __as__12EvalFrameRefP9EvalFrame(p, pt->x0);
    if (pp)
        *pp = p;
    for (i = 0; i < pt->c4C; i++) {
        struct E50 *pe = &pt->ae50[i];
        if (!(pe->k & 0x40000000)) {
            int a;
            struct B98 *b;
            func_00136E28(pt, x, pe, &a, &b);
            if (b) {
                func_00241F00(a, 0);
                struct N34 *pn = (struct N34 *)func_0014BE38(0x2C);
                func_002BBC38(pn);
                pn->x0 = 0;
                pn->pvt = D_00351CE8;
                if (pe->k & 0x80000000)
                    pn->x20 = pe->x4;
                else
                    pn->x1C = pe->x4;
                pn->x4 = a;
                pn->x8 = b;
                pn->xC = pt->x5C;
                pn->p24 = p;
                if (b->s98 == 6)
                    pn->x14 = 6;
                else
                    pn->x14 = (grf & 1) ? 8 : 5;
                pn->pnNext = p->pn34;
                p->pn34 = pn;
                func_0028ECE0(a, b, pn);
            }
        }
    }
    for (j = 0; j < pt->c54; j++) {
        struct E58 *pe = &pt->ae58[j];
        int a, b;
        func_00136FC8(pt, x, pe, &a, &b);
        if (b) {
            struct N38 *pn = (struct N38 *)func_0012F240(0x14);
            pn->x0 = pe->x8;
            pn->x4 = b;
            pn->x8 = a;
            pn->xC = pe->x0;
            pn->pnNext = p->pn38;
            p->pn38 = pn;
            P *po = (P *)a;
            ((void (*)(P *, int))po->pvt[48].pfn)((P *)((char *)po + po->pvt[48].d), pe->x0);
        }
    }
    func_00138AF0(p, pt->x60);
    p->g20 = g0;
    for (k = 0; k < pt->cev; k++)
        func_00138270(p, &pt->aev[k]);
    p->g1C = p->g20;
    func_0028F978(p, (grf >> 2) & 1);
    if ((grf & 2) && ((0.0f < p->g40 && 0.0f < p->g1C) || (p->g40 < 0.0f && p->g1C < pt->g64))) {
        if (p->g40 < 0.0f)
            p->x50 = pt->x90;
        func_001380E0(p);
    } else {
        func_00137EA0(p);
    }
    if (grf & 1) {
        float *pg = func_00136880(pt, 0x1CD);
        if (pg)
            func_00138BF8(p, g_clock.t + *pg / p->g40);
    }
    ((void (*)(P *, int, int, int, int, int))p->pvt[3].pfn)((P *)((char *)p + p->pvt[3].d), 2, 0, 0, 0, 0);
}
