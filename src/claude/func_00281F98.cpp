// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef unsigned short ushort;
union UQ { qword q; float f[4]; };
struct EDGE { ushort ivA, ivB, pad4, iface; EDGE *next; };
struct FACE { qword eq; EDGE *pedge; int x14; int grf; int x1C; };
struct NODE { int x0, x4, x8; };
struct TREE { int x0, x4, cnode; NODE *anode; };
struct GEOM { int x0; qword *avert; int x8; FACE *aface; };
struct OHDR { char pad[0xA4]; int frame; };
struct O {
    OHDR *phdr; char pad4[0x78 - 4]; TREE tree;
    char pad88[0xA0 - 0x88]; GEOM geom; char padB0[0xC0 - 0xB0]; int frame;
};
struct VTE { short d; short pad; void *(*pfn)(void *); };
struct VT { char pad[0x120]; VTE e120; };
struct XF { char pad[0x30]; qword pos; };
struct LO { char pad[0xC]; VT *pvt; char pad10[0x440 - 0x10]; int frame; };
struct ENT { LO *plo; int frame; float sHeight; };
struct WAYPT {
    char pad[0xC]; VT *pvt; char pad10[0x148 - 0x10];
    LO *ploSource;          // 0x148
    char pad14C[0x15C - 0x14C];
    int cent;               // 0x15C
    ENT aent[4];            // 0x160
    char pad190[0x1A4 - 0x190];
    int fFixed;             // 0x1A4
    float sFixed;           // 0x1A8
    int k;                  // 0x1AC
};
struct P4 { qword q; };
struct REQ { int cb, align; };
struct FRAME { int x[4]; };
extern char D_00475480[];
extern qword D_00317550;
extern "C" {
void func_00119E20(UQ *, qword, qword, qword);
void func_00119EA8(UQ *, qword, qword);
UQ *func_002BA008(UQ *);
UQ *func_002BA000(UQ *);
FRAME *func_001D2770(FRAME *);
void func_001D2798(FRAME *, int);
void *func_001D25B0(REQ *);
int func_00167578(void *, O *);
void func_0025CF18(void *, qword, qword, int (*)(void *, O *), void *, int *, O ***);
int func_00119C58(NODE *, NODE *, int, UQ *, int *, FACE ***);
void func_0018B1E0(O *);
}
#define func_002564B8 func_002BA000
static inline XF *XfOf(LO *p) { VTE *e = &p->pvt->e120; return (XF *)e->pfn((char *)p + e->d); }
static inline qword PosOfLo(LO *p) { return XfOf(p)->pos; }
static inline void Plane3(UQ &r, qword a, qword b, qword c) { func_00119E20(&r, a, b, c); }
static inline qword Q(float f)
{ qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(f)); return r; }
static inline qword QI(int i)
{ qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "rV"(i)); return r; }
static inline qword ToR2(qword q, qword d)
{ qword r; __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(q), "j"(d)); return r; }
static inline qword AddUp(qword base, qword up, qword k)
{ qword r; __asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base), "j"(up), "j"(k)); return r; }
static inline qword AddUpU(qword base, qword up, qword k)
{ qword r; __asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base), "j"(up), "j"(k), "j"(up), "j"(up)); return r; }
static inline qword Sub(qword a, qword b)
{ qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Max(qword a, qword b)
{ qword r; __asm__("vmax.xyz %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Min(qword a, qword b)
{ qword r; __asm__("vmini.xyz %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Cross(qword a, qword b)
{ qword r; __asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Normalize(qword v)
{
    qword d, one, r;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %1,$vf0,Q\n\tvdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q" : "=j"(r), "+j"(d) : "j"(v) : "v0"); // v0 clobber: gives the nrm store (sq v0) an anti-dep on this asm after reload, so sched2 issues it before the vmul
    __asm__("" : "+j"(r) : "j"(v) : "memory");
    return r;
}
static inline float ZOfP(qword v)
{ float z; __asm__("pextuw %0,$zero,%1" : "=r"(z) : "r"(v)); return z; }
static inline float FQ(qword q)
{ float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline float FG(qword q)
{ float f; __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(q)); return f; }
static inline float LenXY(qword v)
{
    qword d, l;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(l) : "j"(d));
    return FQ(l);
}
static inline float PlaneDistA(UQ &r, UQ &one, qword plane, qword pos)
{
    qword g, o;
    func_002564B8(&r);
    func_002564B8(&one);
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddaz.x ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(g), "=j"(o) : "j"(plane), "j"(pos));
    float f = FG(g);
    one.q = o;
    r.q = g;
    return f;
}

static inline float PlaneDistB(UQ &r, UQ &one, qword plane, qword pos)
{
    qword g, o;
    func_002564B8(&r);
    func_002564B8(&one);
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddaz.x ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(g), "=j"(o) : "j"(plane), "j"(pos));
    float f = FQ(g);
    __asm__("" : "+j"(g), "+j"(o));
    one.q = o;
    r.q = g;
    return f;
}

static inline float PlaneDistS(UQ &r, UQ &one, qword plane, qword pos)
{
    qword g, o;
    func_002564B8(&r);
    func_002564B8(&one);
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddaz.x ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(g), "=j"(o) : "j"(plane), "j"(pos));
    float f = FQ(g);
    __asm__("" : "+j"(g));
    one.q = o;
    r.q = g;
    return f;
}


static inline float LenXYF(qword v)
{
    qword d, l;
    float f;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(l) : "j"(d));
    __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(l));
    return f;
}
static inline GEOM *PgeomOf(O *p) { if (p->frame != p->phdr->frame) func_0018B1E0(p); return &p->geom; }
static inline TREE *PtreeOf(O *p) { if (p->frame != p->phdr->frame) func_0018B1E0(p); return &p->tree; }
extern "C" void func_00281F98(WAYPT *pwaypt)
{
    int ient = 0;
    if (pwaypt->cent > 0) do {
    UQ corner[4];
    UQ side[4];
    UQ tmp;
    FRAME frame;
    UQ nrm;
    struct { int cpso; O **apso; int cface; FACE **ppface; } L;
#define cpso L.cpso
#define apso L.apso
#define cface L.cface
#define ppface L.ppface
    ENT *pent = &pwaypt->aent[ient];
    LO *plo = pent->plo;
    if (pent->frame == plo->frame)
        continue;
    pent->frame = plo->frame;
    if (pwaypt->fFixed) {
        pent->sHeight = pwaypt->sFixed;
        continue;
    }
    qword posCam = PosOfLo(plo);
    LO *psrc = pwaypt->ploSource;
    register qword rr asm("$6"); // pin
    if (psrc)
        rr = PosOfLo(psrc);
    else
        rr = PosOfLo((LO *)pwaypt);
    qword posSrc = rr;
    pent->sHeight = 0.0f;

    corner[0].q = posSrc;
    qword up = D_00317550;
    qword k = QI(pwaypt->k);
    qword v1 = AddUpU(posSrc, up, k);
    qword v2 = AddUpU(posCam, up, k);
    tmp.q = k;
    corner[2].q = v2;
    corner[1].q = v1;
    corner[3].q = posCam;
    Plane3(tmp, posCam, posSrc, corner[1].q);
    qword plane = tmp.q;
    P4 pvA, pvB;

    int i;
    FACE **apface;
    int ipso;
    int c;
    EDGE *pe;
    FACE *pf;
    for (i = 0; i < 4; i++) {
        UQ *pc = corner;
        qword edge = Sub(pc[(i + 1) % 4].q, pc[i].q);
        func_002BA008(&nrm);
        qword cr = Cross(edge, plane);
        nrm.q = ToR2(plane, cr);
        func_00119EA8(&side[i], Normalize(cr), pc[i].q);
    }
    ipso = 0;
    func_001D2770(&frame);
    REQ *preq = (REQ *)&tmp;
    preq->cb = 0x10000;
    preq->align = 16;
    apface = (FACE **)func_001D25B0(preq);
    qword k2 = QI(pwaypt->k);
    tmp.q = k2;
    func_0025CF18(D_00475480, Min(posCam, posSrc), AddUp(Max(posCam, posSrc), D_00317550, k2),
                  func_00167578, 0, &cpso, &apso);
    qword dpos = Sub(posSrc, posCam);
    int nso = cpso;
    float z;
    __asm__("qmfc2.ni %0,%1\n\tpextuw %0,$zero,%0" : "=r"(z) : "j"(dpos));
    float sMax = z / LenXYF(dpos);
    float sBase = sMax;
    for (; ipso < cpso; ipso++) {
        O *pso = apso[ipso];
        GEOM *pgeom = PgeomOf(pso);
        TREE *ptree = PtreeOf(pso);
        NODE *pn = ptree->anode;
        NODE *pnLim = pn + ptree->cnode;
        cface = 0x4000;
        ppface = apface;
        int res = func_00119C58(pn, pnLim, 4, corner, &cface, &ppface);
        switch (res) { case 0: func_001D2798(&frame, 2); return; case 1: continue; case 2: break; }
        c = ppface - apface;
        UQ d[6][2];
        int j;
        for (j = 0; j < c; j++) {
            for (pf = apface[j], pe = pf->pedge; pe; pe = pe->next) {
                FACE *pfa = &pgeom->aface[pe->iface];
                if (!(pfa->grf & 0x4000))
                    continue;
                int ia = pe->ivA;
                int ib = pe->ivB;
                P4 *av = (P4 *)pgeom->avert;
                P4 *pa = (P4 *)(((int)ia << 4) + (int)av);
                P4 *pb = (P4 *)(((int)ib << 4) + (int)av);
                P4 ta = *pa;
                P4 tb = *pb;
                pvA = ta;
                pvB = tb;
                float gA = PlaneDistA(d[0][0], d[0][1], plane, pvA.q);
                float gB = PlaneDistB(d[1][0], d[1][1], plane, pvB.q);
                if (0.0f < gA && 0.0f < gB)
                    continue;
                if (gA < 0.0f && gB < 0.0f)
                    continue;
                float u = gA / (gA - gB);
                qword qa = Q(1.0f - u);
                tmp.q = qa;
                qword qb = Q(u);
                tmp.q = qb;
                qword posX;
                __asm__("vmulax.xyzw ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x" : "=j"(posX) : "j"(pvA.q), "j"(pvB.q), "j"(qa), "j"(qb));
                int fIn = 0;
                if (PlaneDistS(d[2][0], d[2][1], side[0].q, posX) < 0.0f &&
                    PlaneDistS(d[3][0], d[3][1], side[1].q, posX) < 0.0f &&
                    PlaneDistS(d[4][0], d[4][1], side[2].q, posX) < 0.0f &&
                    PlaneDistS(d[5][0], d[5][1], side[3].q, posX) < 0.0f)
                    fIn = 1;
                if (fIn) {
                    qword dx = Sub(posX, posCam);
                    float s = ZOfP(dx) / LenXY(dx);
                    if (sMax < s && s < 0.7f)
                        sMax = s;
                }
            }
        }
        for (j = 0; j < c; j++)
            { pf = apface[j]; pf->grf &= ~0x4000; }
    }
    pent->sHeight = (sMax - sBase) * LenXY(Sub(posCam, posSrc));
    func_001D2798(&frame, 2);
#undef cpso
#undef apso
#undef cface
#undef ppface
    } while (++ient < pwaypt->cent);
}
