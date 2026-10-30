// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Splice GC mark phase (Sly 2 func_001286E0 shape, Sly 3 pools; mark bit 31, next idx bits 20-30, page bits 16-19). */
struct N { int x0; int w; };
struct M { int x0; int x4; int w; };
struct BIND { int x0; int w; int x8; int ref[2]; BIND *pbNext; };
struct ENV { int x0; int w; BIND *pbFirst; };
struct ROOT { int x0; int x4; M *pobj; int xC; ROOT *prNext; };
struct GC { int f; int cFrame; void **apFrame; int cNode; void **apNode; int cClo; void **apClo; };
struct ALLOCREQ { int cb; int cbAlign; };
void *PvAllocSlot(ALLOCREQ *);
struct CTX { int a[4]; CTX(); ~CTX(); };
extern "C" void func_002BB770(void *, int);
struct LOCK { int a[4]; LOCK() {} ~LOCK() { func_002BB770(this, 2); } };
extern "C" {
extern char *D_004D2BC8[];
extern char *D_004D2A18[];
extern char *D_004D2D78[];
extern int D_004D2C98, D_004D2AE8, D_004D2D70;
extern N *D_0036AE38;
extern M *D_0036AE10;
extern ENV *D_0036AE60;
extern ROOT *D_004793A0;
extern int D_0036B138;
void func_002BAF38(void);
void func_002BAF40(void);
void func_002BAF48(void);
void func_002BAF50(void);
void func_002BAF58(void);
void func_002BAF60(void);
void func_002BAF68(void);
void func_002BB0C0(void);
void func_002BB218(void);
void func_002BB368(void);
void func_002BB4C0(void);
void func_002BB618(void);
void func_0012A2C8(GC *, void *);
void func_00129E88(GC *);
}

static inline ALLOCREQ *Req(ALLOCREQ *preq, int cb, int cbAlign)
{
    preq->cb = cb;
    preq->cbAlign = cbAlign;
    return preq;
}
static inline void InitStack(int *pc, void ***pap, int c, ALLOCREQ *preq)
{
    *pap = (void **)PvAllocSlot(Req(preq, c * 4, 0x10));
    *pc = 0;
}
static inline int SetMark(int w) { return (w & 0x7FFFFFFF) | (D_0036B138 << 31); }
#define DEFPTR(name, T, apb, cb) static inline T *name(unsigned pg, unsigned idx) { if (pg == 0 && idx == 0) return 0; return (T *)(apb[pg] + idx * cb); }
DEFPTR(PtrN, N, D_004D2BC8, 0x18)
DEFPTR(PtrM, M, D_004D2A18, 0x10)
DEFPTR(PtrEnv, ENV, D_004D2D78, 0xC)
#define PG(w) (((unsigned)(w) >> 16) & 0xF)
#define IDX(w) (((unsigned)(w) >> 20) & 0x7FF)

extern "C" void func_0012A3D0(GC *pgc)
{
    int zero = 0;
    pgc->f = !pgc->f;
    func_002BAF38();
    func_002BAF40();
    func_002BAF48();
    func_002BAF50();
    func_002BAF58();
    func_002BAF60();
    CTX ctx;
    ALLOCREQ req;
    InitStack(&pgc->cFrame, &pgc->apFrame, D_004D2C98, &req);
    InitStack(&pgc->cNode, &pgc->apNode, D_004D2AE8, &req);
    pgc->apClo = (void **)PvAllocSlot(Req(&req, D_004D2D70 * 4, 0x10));
    pgc->cClo = 0;
    {
    LOCK lock;
    for (N *pn = D_0036AE38; pn; ) {
        if ((pn->w < zero) != D_0036B138) {
            pn->w = SetMark(pn->w);
            pgc->apFrame[pgc->cFrame++] = pn;
        }
        { N *pNext = PtrN(PG(pn->w), IDX(pn->w)); pn = pNext; }
    }
    for (M *pm = D_0036AE10; pm; ) {
        if ((pm->w < zero) != D_0036B138) {
            pm->w = SetMark(pm->w);
            pgc->apNode[pgc->cNode++] = pm;
        }
        { M *pNext = PtrM(PG(pm->w), IDX(pm->w)); pm = pNext; }
    }
    for (ENV *penv = D_0036AE60; penv; ) {
        { int mark = D_0036B138; if ((penv->w < zero) != mark) penv->w = SetMark(penv->w); }
        for (BIND *pb = penv->pbFirst; pb; pb = pb->pbNext) {
            pb->w = (pb->w & 0x7FFFFFFF) | ((unsigned short)D_0036B138 << 31);
            func_0012A2C8(pgc, pb->ref);
        }
        { ENV *pNext = PtrEnv(PG(penv->w), IDX(penv->w)); penv = pNext; }
    }
    for (ROOT *pr = D_004793A0; pr; pr = pr->prNext) {
        M *p = pr->pobj;
        if ((p->w < zero) != D_0036B138) {
            p->w = SetMark(p->w);
            pgc->apNode[pgc->cNode++] = p;
        }
    }
    }
    func_00129E88(pgc);
    func_002BAF68();
    func_002BB0C0();
    func_002BB218();
    func_002BB368();
    func_002BB4C0();
    func_002BB618();
}
