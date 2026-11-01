// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// A* search over the path graph: from pvStart to pvGoal, writes the vertices of the best route (start first) into apv
// and their count into *pc (0 when the goal is unreachable). Based on Sly 2 func_001BF980.
typedef int qword __attribute__((mode(TI)));
struct FRAME { char b; FRAME(); ~FRAME(); };
struct AREQ { int cb; int align; AREQ(int c, int a) { cb = c; align = a; } };
struct V;
struct E { V *pv; float cost; };
struct V { qword pos; int cEdge; E *aEdge; };
struct G { int c; };
struct NODE { V *pv; float f; float g; NODE *parent; int depth; NODE *next; };
extern "C" {
void *func_001D25B0(const AREQ &r);
void *func_001D2670(const AREQ &r);
int func_001EBD40(G *p, V *pv);
}
static inline void *Alloc(int cb) { return func_001D25B0(AREQ(cb, 0x10)); }
static inline void *AllocB(int cb) { return func_001D2670(AREQ(cb, 0x10)); }
static inline float Dist2(const qword &a, const qword &b)
{
    qword d;
    float r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(d));
    return r;
}

extern "C" void func_001EBD50(G *p, V *pvStart, V *pvGoal, int cMax, int *pc, V **apv)
{
    int *afClosed;
    NODE node;
    FRAME ctx;
    NODE *pnHead;
    NODE *pn;
    afClosed = (int *)AllocB(p->c << 2);
    apv[0] = pvStart;
    pnHead = 0;
    node.depth = 1;
    node.pv = pvStart;
    node.f = Dist2(pvStart->pos, pvGoal->pos);
    node.g = 0.0f;
    node.parent = 0;
    pn = &node;
    if (pvStart != pvGoal) {
        do {
            V *pvCur = pn->pv;
            int i;
            for (i = 0; i < pvCur->cEdge; i++) {
                E *pe = &pvCur->aEdge[i];
                V *pv = pe->pv;
                int fSkip;
                NODE *pnNew, **ppn, *pnT;
                if (pv == pvGoal) {
                    fSkip = 0;
                } else {
                    int iv = func_001EBD40(p, pv);
                    if (afClosed[iv] == 0) {
                        afClosed[iv] = 1;
                        fSkip = 0;
                    } else {
                        fSkip = 1;
                    }
                }
                if (fSkip)
                    continue;
                pnNew = (NODE *)Alloc(0x18);
                pnNew->pv = pv;
                pnNew->g = pn->g + pe->cost;
                pnNew->f = pnNew->g + Dist2(pvCur->pos, pvGoal->pos);
                pnNew->parent = pn;
                pnNew->depth = pn->depth + 1;
                ppn = &pnHead;
                for (pnT = pnHead; pnT; pnT = pnT->next) {
                    if (pnNew->f < pnT->f)
                        break;
                    ppn = &pnT->next;
                }
                pnNew->next = pnT;
                *ppn = pnNew;
            }
            pn = pnHead;
            if (!pn)
                break;
            pnHead = pn->next;
        } while (pn->pv != pvGoal);
    }
    if (pn) {
        *pc = pn->depth;
        for (; pn; pn = pn->parent)
            apv[pn->depth - 1] = pn->pv;
    } else {
        *pc = 0;
    }
}
