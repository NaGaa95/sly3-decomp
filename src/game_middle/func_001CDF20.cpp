// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Contact generation between two collision objects (SO): every shape pair of the two objects, with bounding-sphere
// rejection, per-shape filters, a refined BSP query for the larger-vs-smaller shape case, then the per-shape sweeps.
typedef int qword __attribute__((mode(TI)));
struct LO { char pad0[0x70]; qword pos; char pad80[0x24]; int version; };
struct FILTER;
struct NODE { NODE *pnodeLeft, *pnodeRight; qword *pplane; };
struct CONTACT;
struct WORLD;
struct VT { short delta, pad; void *fn; };
struct OWNER { char pad0[0xC]; VT *vt; };
struct SHAPE;
struct POINTS { int unk0; int cnodeMax; int unk8; NODE *pnodeRoot; };
struct SHAPE {
    LO *plo;                                // 0x00
    FILTER *pfilter;                        // 0x04
    float sRadius;                          // 0x08
    float sRadiusBound;                     // 0x0C
    char pad10[8];
    union { unsigned long grf; struct { unsigned grfLo; int grfFilter; } f; };   // 0x18
    int iFirst;                             // 0x20
    char pad24[0x70 - 0x24];
    SHAPE *pshapeNext;                      // 0x70
    char pad74[4];
    POINTS points;                          // 0x78
    int c;                                  // 0x88
    char pad8C[0xB8 - 0x8C];
    int gen, genOld;                        // 0xB8, 0xBC
    int version;                            // 0xC0
};
struct SO {
    char pad0[0x20];
    qword pos;                              // 0x20
    float sRadius;                          // 0x30
    SHAPE *pshapeFirst;                     // 0x34
    SHAPE *pshapeLast;                      // 0x38
    char pad3C[0x60 - 0x3C];
    OWNER *owner;                           // 0x60
    char pad64[8];
    CONTACT *pcontactFirst;                 // 0x6C
    unsigned long grf;                      // 0x70
};
extern "C" {
void func_001D2770(void *);
void func_001D2798(void *, int);
void func_002BC900(void *, int);
}
struct GUARD { ~GUARD() { func_002BC900(this, 2); } };
struct FRAME { FRAME(); ~FRAME(); };
struct SCOPES { GUARD g0; GUARD g1; FRAME frame; inline SCOPES() {} inline ~SCOPES() {} };
struct ALLOCREQ { int cb, cbAlign; ALLOCREQ(int c, int a) { cb = c; cbAlign = a; } };
extern NODE D_00341E00;
extern "C" {
void *func_001D25B0(const ALLOCREQ &req);
void func_0018B1E0(SHAPE *pshape);
int func_00119C20(NODE *pnode, int cnodeMax, qword pos, float sRadius, int *pcnode, NODE **ppnode);
int func_00240E10(FILTER *pfilter, int grf);
void func_001CDA68(WORLD *pworld, SHAPE *pshape, SHAPE *pshapeOther, CONTACT **ppcontact);
void func_001CD970(WORLD *pworld, SHAPE *pshape, SHAPE *pshapeOther, CONTACT **ppcontact);
void func_001CD858(WORLD *pworld, SHAPE *pshape, SHAPE *pshapeOther, int cnode, NODE *pnode, CONTACT **ppcontact);
void func_001CC790(WORLD *pworld, SHAPE *pshape, SHAPE *pshapeOther, int cnode, NODE *pnode, NODE *pnodeLast, CONTACT **ppcontact);
void func_001CDD30(WORLD *pworld, CONTACT *pcontact, CONTACT **ppcontact);
CONTACT *func_001CDD78(WORLD *pworld, CONTACT *pcontact);
void func_001CDE08(WORLD *pworld, SO *pso, SO *psoOther, SHAPE *pshape, int cnode, NODE *pnode, NODE *pnodeLast, CONTACT **ppcontact);
}
static inline float LengthSq(qword v)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("mtc1 %1,%0" : "=f"(g) : "r"(d), "j"(d));
    return g;
}
static inline qword PosOf(const qword *p) { return *p; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline int NMin(int a, int b) { return (a < b) ? a : b; }
static inline int Separated(SHAPE *a, SHAPE *b)
{
    float sum = a->sRadiusBound + b->sRadiusBound;
    return sum * sum < LengthSq(Sub(a->plo->pos, b->plo->pos));
}
static inline POINTS *Points(SHAPE *pshape)
{
    if (pshape->version != pshape->plo->version)
        func_0018B1E0(pshape);
    return &pshape->points;
}
#define SHAPE_FILTERED (1UL << 16)
#define SHAPE_SPHERE (1UL << 17)

extern "C" CONTACT *func_001CDF20(WORLD *pworld, SO *psoSmall, SO *psoLarge)
{
    CONTACT *pcontactFirst = 0;
    SO *psoT = psoSmall;
    if (psoSmall->sRadius > psoLarge->sRadius) {
        psoSmall = psoLarge;
        psoLarge = psoT;
    }
    int cnodeMax = 0;
    SHAPE *pshape;
    SHAPE *pshapeOther;
    NODE *anode;
    for (pshape = psoLarge->pshapeFirst; pshape; pshape = pshape->pshapeNext)
        if (cnodeMax < pshape->points.cnodeMax)
            cnodeMax = pshape->points.cnodeMax;
    SCOPES scopes;
    cnodeMax = NMin(cnodeMax, 0x1555);
    anode = (NODE *)func_001D25B0(ALLOCREQ(cnodeMax * sizeof(NODE), 0x10));
    for (pshape = psoLarge->pshapeFirst; pshape; pshape = pshape->pshapeNext) {
        int fFilter = pshape->f.grfFilter != 0;
        if ((pshape->grf & SHAPE_FILTERED) && !fFilter)
            continue;
        NODE *pnodeFirst;
        NODE *pnodeLast;
        int cnode;
        int status = 2;
        if ((pshape->grf & SHAPE_SPHERE) || (psoSmall->grf & 0x20)) {
            pnodeLast = 0;
            pnodeFirst = 0;
            cnode = 0;
        } else {
            int cquery = cnodeMax;
            pnodeLast = anode;
            pnodeFirst = anode;
            status = func_00119C20(Points(pshape)->pnodeRoot, 0x7FFFFFFF, psoSmall->pos, psoSmall->sRadius, &cquery, &pnodeLast);
            if (status == 1)
                continue;
            if (status == 0) {
                cnode = 0;
                pnodeLast = &D_00341E00;
                pnodeFirst = &D_00341E00;
            } else {
                cnode = pnodeLast - pnodeFirst;
                pnodeLast--;
            }
        }
        for (pshapeOther = psoSmall->pshapeFirst; pshapeOther; pshapeOther = pshapeOther->pshapeNext) {
            int fFilterOther = pshapeOther->f.grfFilter != 0;
            if ((pshapeOther->grf & SHAPE_FILTERED) && !fFilterOther)
                continue;
            if ((pshape->grf & SHAPE_FILTERED) && (pshapeOther->grf & SHAPE_FILTERED))
                continue;
            CONTACT *pcontactTemp = 0;
            CONTACT **ppcontact = &pcontactFirst;
            if (fFilter) {
                int fMatch = func_00240E10(pshapeOther->pfilter, pshape->f.grfFilter) != 0;
                if (pshape->grf & SHAPE_FILTERED) {
                    if (!fMatch)
                        continue;
                    ppcontact = &pcontactTemp;
                } else if (fMatch) {
                    if (!(pshapeOther->grf & SHAPE_FILTERED))
                        ppcontact = &pcontactTemp;
                }
            }
            if (fFilterOther) {
                int fMatch = func_00240E10(pshape->pfilter, pshapeOther->f.grfFilter) != 0;
                if (pshapeOther->grf & SHAPE_FILTERED) {
                    if (!fMatch)
                        continue;
                    ppcontact = &pcontactTemp;
                } else if (fMatch && !(pshape->grf & SHAPE_FILTERED)) {
                    ppcontact = &pcontactTemp;
                }
            }
            if (Separated(pshapeOther, pshape))
                continue;
            CONTACT *pcontactPrev = *ppcontact;
            if (pshapeOther->gen != pshapeOther->genOld || pshape->gen != pshape->genOld) {
                if (pshapeOther->iFirst < pshapeOther->c)
                    func_001CDA68(pworld, pshapeOther, pshape, ppcontact);
                if (pshape->iFirst < pshape->c)
                    func_001CDA68(pworld, pshape, pshapeOther, ppcontact);
            }
            if (*ppcontact == pcontactPrev) {
                if (pshape->grf & SHAPE_SPHERE) {
                    if (pshapeOther->grf & SHAPE_SPHERE)
                        func_001CD970(pworld, pshapeOther, pshape, ppcontact);
                    else
                        func_001CD858(pworld, pshape, pshapeOther, 0, 0, ppcontact);
                } else if (pshapeOther->grf & SHAPE_SPHERE) {
                    int fFar = 0;
                    if (!status || 1.0f < LengthSq(Sub(pshape->plo->pos, psoSmall->pos)) ||
                        1.0f < __builtin_fabsf(pshape->sRadius - psoSmall->sRadius))
                        fFar = 1;
                    func_001CD858(pworld, pshapeOther, pshape, fFar ? 0 : cnode, fFar ? 0 : pnodeFirst, ppcontact);
                } else {
                    FRAME frame2;
                    NODE *pnodeFirst2 = pnodeFirst;
                    NODE *pnodeLast2 = pnodeLast;
                    int cnode2 = cnode;
                    if (pshapeOther->sRadiusBound < psoSmall->sRadius * 0.9f && psoSmall->pshapeFirst != psoSmall->pshapeLast &&
                        !(psoSmall->grf & 0x20) && cnode >= 21 && (unsigned)(cnode * 2) < 0x1555) {
                        int c2;
                        NODE *pn = (NODE *)func_001D25B0(ALLOCREQ(cnode * sizeof(NODE), 0x10));
                        pnodeLast2 = pn;
                        pnodeFirst2 = pn;
                        c2 = cnodeMax;
                        status = func_00119C20(pnodeLast, 0x7FFFFFFF, PosOf(&pshapeOther->plo->pos), pshapeOther->sRadiusBound, &c2, &pnodeLast2);
                        if (status == 1)
                            continue;
                        if (status == 0) {
                            cnode2 = 0;
                            pnodeLast2 = &D_00341E00;
                            pnodeFirst2 = &D_00341E00;
                        } else {
                            cnode2 = pnodeLast2 - pnodeFirst2;
                            pnodeLast2--;
                        }
                    }
                    func_001CC790(pworld, pshapeOther, pshape, cnode2, pnodeFirst2, pnodeLast2, ppcontact);
                }
            }
            if (pcontactTemp) {
                int fCopied = 0;
                if (fFilter) {
                    if (pshape->grf & SHAPE_FILTERED)
                        func_001CDD30(pworld, pcontactTemp, &psoLarge->pcontactFirst);
                    else if (!(pshapeOther->grf & SHAPE_FILTERED)) {
                        fCopied = 1;
                        func_001CDD30(pworld, func_001CDD78(pworld, pcontactTemp), &psoLarge->pcontactFirst);
                    }
                }
                if (fFilterOther) {
                    if (pshapeOther->grf & SHAPE_FILTERED)
                        func_001CDD30(pworld, pcontactTemp, &psoSmall->pcontactFirst);
                    else if (!(pshape->grf & SHAPE_FILTERED)) {
                        fCopied = 1;
                        func_001CDD30(pworld, func_001CDD78(pworld, pcontactTemp), &psoSmall->pcontactFirst);
                    }
                }
                if (fCopied)
                    func_001CDD30(pworld, pcontactTemp, &pcontactFirst);
            }
        }
        if (!(pshape->grf & SHAPE_FILTERED))
            func_001CDE08(pworld, psoSmall, psoLarge, pshape, cnode, pnodeFirst, pnodeLast, &pcontactFirst);
    }
    for (pshapeOther = psoSmall->pshapeFirst; pshapeOther; pshapeOther = pshapeOther->pshapeNext)
        if (!(pshapeOther->grf & SHAPE_FILTERED)) {
            POINTS *pp = Points(pshapeOther);
            func_001CDE08(pworld, psoLarge, psoSmall, pshapeOther, pp->cnodeMax, pp->pnodeRoot, pp->pnodeRoot, &pcontactFirst);
        }
    {
        CONTACT **ppc = &pcontactFirst;
        OWNER *o0 = psoSmall->owner, *o1 = psoLarge->owner;
        ((void (*)(void *, OWNER *, CONTACT **))o0->vt[64].fn)((char *)o0 + o0->vt[64].delta, o1, ppc);
        ((void (*)(void *, OWNER *, CONTACT **))psoLarge->owner->vt[64].fn)((char *)psoLarge->owner + psoLarge->owner->vt[64].delta, psoSmall->owner, ppc);
    }
    return pcontactFirst;
}
