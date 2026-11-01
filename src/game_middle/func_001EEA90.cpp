// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// A* path search over the navigation polygons: returns the number of edges written to apedge (based on Sly 2 func_001C21D8).
// StoreX stores the VU length bits straight from the integer register, as the original does.
typedef int qword __attribute__((mode(TI)));
struct MSG { int cb; int nKind; };
struct DL { void *pvFirst; void *pvLast; int ibDle; };
struct NAV { char pad[0x114]; int index; };
struct EDGE { char pad[0x118]; NAV *pnavDest; int pad11C; qword posBegin; qword posEnd; };
struct VTE { short delta; short pad; void *(*method)(void *); };
struct ACTOR { char pad[0xC]; VTE *vt; };
struct POS { char pad[0x30]; qword pos; };
#define VCALL(po, n) ((po)->vt[n].method((char *)(po) + (po)->vt[n].delta))
struct ADJ { int cedge; int *aiedge; };
struct GRAPH { char pad[0x10]; int cnav; char pad14[8]; ADJ *aadj; int cedge; EDGE **apedge; };
struct NODE { NAV *pnav; EDGE *pedge; NODE *pnodeParent; float gCost; float gEstimate; int state; NODE *pnodeNext; NODE *pnodePrev; };

extern "C" {
void *func_001D2670(MSG *pmsg);
void *func_001D25B0(MSG *pmsg);
void *func_00292034(void *pv, int b, unsigned int cb);
NAV *func_001ED678(qword pos, int f);
void func_0011AF40(DL *pdl);
void func_002BE868(void *object, int flags);
void func_0011AF38(DL *pdl, int ibDle);
void func_0011AF60(DL *pdl, void *pv);
void func_0011B028(DL *pdl, void *pv);
void func_0011AFC0(DL *pdl, void *pvNext, void *pv);
int func_0011B0F0(DL *pdl);
int func_001EEFB0(GRAPH *pgraph, EDGE *pedge, void *pvActor);
int func_001ED170(NAV *pnav, qword pos, int f);
}

static inline void *PvAllocClear(int cb) { MSG msg; msg.cb = cb; msg.nKind = 0x10; return func_001D2670(&msg); }
static inline void *PvAlloc(int cb) { MSG msg; msg.cb = cb; msg.nKind = 0x10; return func_001D25B0(&msg); }
// The current stack-allocation scope (out-of-line ctor/dtor at 0x1D2770 / 0x1D2798)
struct FRAME { char b; FRAME(); ~FRAME(); };
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwLength(qword v)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=j"(vfOne) : "j"(v), "j"(v));

    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
// Scope object of the open-list scan; its destructor is the out-of-line release stub at 0x2BE868
struct SCAN { char b; ~SCAN() { func_002BE868(this, 2); } };
static inline NAV *PnavFind(const qword &pos) { return func_001ED678(pos, 0); }
static inline void AppendNode(DL *pdl, NODE *pnode) { func_0011AF60(pdl, pnode); }
static inline void RemoveNode(DL *pdl, NODE *pnode) { func_0011B028(pdl, pnode); }
static inline void InsertNode(DL *pdl, NODE *pnodeNext, NODE *pnode) { func_0011AFC0(pdl, pnodeNext, pnode); }
static inline float GXOfQw(qword qw) { float x; __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw)); return x; }
static inline float GDistX(const qword &a, const qword &b) { return GXOfQw(QwLength(QwSub(a, b))); }

static inline void StoreX(float *p, qword q) { __asm__("sw %1,%0" : "=m"(*p) : "r"(q)); }
extern "C" int func_001EEA90(GRAPH *pgraph, ACTOR *pvActor, qword posGoal, int fExact, int cpedgeMax, EDGE **apedge)
{
    FRAME scope;
    NODE *anode;
    int *afAllowed;
    anode = (NODE *)PvAllocClear(pgraph->cnav * sizeof(NODE));
    afAllowed = (int *)PvAlloc(pgraph->cedge * sizeof(int));
    func_00292034(afAllowed, 0xFF, pgraph->cedge * sizeof(int));
    qword posStart = ((POS *)VCALL(pvActor, 36))->pos;
    NAV *pnavStart = PnavFind(posStart);
    NAV *pnavGoal = PnavFind(posGoal);

    if (!pnavStart || !pnavGoal) {
        return 0;
    }
    DL dlOpen;
    DL dlClosed;
    func_0011AF40(&dlOpen);
    func_0011AF38(&dlOpen, 0x18);
    func_0011AF40(&dlClosed);
    func_0011AF38(&dlClosed, 0x18);
    NODE *pnode = &anode[pnavStart->index];
    pnode->pnav = pnavStart;
    StoreX(&pnode->gEstimate, QwLength(QwSub(posStart, posGoal)));


    pnode->state = 2;
    AppendNode(&dlOpen, pnode);
    while (!func_0011B0F0(&dlOpen)) {
        pnode = (NODE *)dlOpen.pvFirst;
        if (fExact) {
            if (pnode->pnav == pnavGoal)
                break;
        } else if (func_001ED170(pnode->pnav, posGoal, 1)) {
            break;
        }
        RemoveNode(&dlOpen, pnode);
        pnode->state = 1;
        AppendNode(&dlClosed, pnode);
        qword posFrom;
        if (pnode->pedge)
            posFrom = pnode->pedge->posEnd;
        else
            posFrom = posStart;
        ADJ *padj = &pgraph->aadj[pnode->pnav->index];
        for (int i = 0; i < padj->cedge; i++) {
            int iedge = padj->aiedge[i];
            EDGE *pedge = pgraph->apedge[iedge];
            if (afAllowed[iedge] == -1)
                afAllowed[iedge] = func_001EEFB0(pgraph, pedge, pvActor);
            if (!afAllowed[iedge])
                continue;

            float gDist = GDistX(posFrom, pedge->posBegin) + GDistX(pedge->posBegin, pedge->posEnd);
            NAV *pnavDest = pedge->pnavDest;
            float gCost = pnode->gCost + gDist;
            NODE *pnodeDest = &anode[pnavDest->index];
            float gEstimate = gCost + GDistX(pedge->posEnd, posGoal);
            if (pnodeDest->state && pnodeDest->gEstimate <= gEstimate)
                continue;
            switch (pnodeDest->state) {
            case 0:
                break;
            case 1:
                RemoveNode(&dlClosed, pnodeDest);
                break;
            case 2:
                RemoveNode(&dlOpen, pnodeDest);
                break;
            }
            pnodeDest->pnav = pnavDest;
            pnodeDest->pedge = pedge;
            pnodeDest->gCost = gCost;
            pnodeDest->pnodeParent = pnode;
            pnodeDest->gEstimate = gEstimate;
            pnodeDest->state = 2;
            NODE *pnodeNext;
            {
                SCAN scan;
                for (pnodeNext = (NODE *)dlOpen.pvFirst; pnodeNext; pnodeNext = pnodeNext->pnodeNext) {
                    if (pnodeNext->gEstimate > pnodeDest->gEstimate)
                        break;
                }
            }
            InsertNode(&dlOpen, pnodeNext, pnodeDest);
        }
    }
    int c = 0;
    if (!func_0011B0F0(&dlOpen)) {
        if (!fExact && !pnode->pnodeParent) {
            apedge[0] = 0;
            c = 1;
        } else {
            int cpedge = 0;
            NODE *pnodeT;
            for (NODE *pnodeCount = pnode; pnodeCount->pnodeParent; pnodeCount = pnodeCount->pnodeParent)
                cpedge++;
            if (cpedge < cpedgeMax)
                c = cpedge;
            else
                c = cpedgeMax;
            for (pnodeT = pnode; pnodeT->pnodeParent; pnodeT = pnodeT->pnodeParent) {
                if (cpedge <= cpedgeMax)
                    apedge[cpedge - 1] = pnodeT->pedge;
                cpedge--;
            }
        }
    }
    return c;
}
