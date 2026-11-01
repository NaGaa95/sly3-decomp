// SLY3_CFLAGS: -Os -G0
// Sample a path from its start to its end in steps of 50.0 and collect (a) the distinct scene objects found at the samples and
// (b) the parameter ranges where consecutive samples do not stay inside one object (joining the first and last range when the
// path is cyclic); both lists are then copied to the heap. Sly 2 func_001E9C88.
// The allocation request is built in pos2's stack slot, as in the Sly 2 source (a separate local changes the frame).
typedef int qword __attribute__((mode(TI)));
struct MSG { int cb; int nKind; };
struct SEG { float a, b; };
struct O { char padC[0xC]; void *vt; char pad10[0xD4-0x10]; int fD4; };
struct S { struct O *po; int c4; struct SEG *aseg; int cC; struct SEG aseg10[16]; int c90; void **apv; int n98; };
float func_0022DFB0(struct O *);
float func_0022DFD8(struct O *);
void func_0022E330(struct O *, float, qword *, qword *);
void *func_001ED678(qword, int);
int func_001ED170(void *, qword, int);
void *func_001D24D0(struct MSG *, void *);
void func_001D2898(void *, const void *, unsigned);
static inline void *PvReallocMsg(struct MSG *pmsg, int cb, int nKind, void *pv) { pmsg->cb = cb; pmsg->nKind = nKind; return func_001D24D0(pmsg, pv); }
void func_002319A0(struct S *ps, struct O *po)
{
    struct SEG aseg[64];
    void *apv[64];
    qword pos;
    qword pos2;
    struct SEG *pseg = 0;
    int cpv = 0;
    int cseg = 0;
    float tStart, tPrev, t, tEnd;
    void *pPrev;

    ps->po = po;
    tStart = func_0022DFB0(po);
    tPrev = tStart;
    t = tStart;
    tEnd = func_0022DFD8(ps->po);
    func_0022E330(ps->po, tStart, &pos, 0);
    pPrev = func_001ED678(pos, 0);
    for (; t < tEnd; t += 50.0f) {
        void *pCur;
        int outside;
        func_0022E330(ps->po, t, &pos2, 0);
        pCur = func_001ED678(pos2, 0);
        if (pCur) {
            int i;
            for (i = 0; i < cpv; i++)
                if (apv[i] == pCur)
                    break;
            if (i >= cpv && (unsigned)cpv < 64)
                apv[cpv++] = pCur;
        }
        outside = 0;
        if (!pCur || pPrev != pCur || !func_001ED170(pPrev, pos2, 0))
            outside = 1;
        if (outside) {
            if (!pseg && cseg < 64) {
                pseg = &aseg[cseg++];
                pseg->a = tPrev;
            }
        } else if (pseg) {
            pseg->b = t;
            pseg = 0;
        }
        tPrev = t;
        pPrev = pCur;
    }
    if (pseg)
        pseg->b = tEnd;
    if (cseg >= 2 && ps->po->fD4 && aseg[0].a == tStart && aseg[cseg - 1].b == tEnd) {
        aseg[0].a = aseg[cseg - 1].a - tEnd;
        aseg[cseg - 1].b = aseg[0].b + tEnd;
    }
    ps->c4 = cseg;
    ps->aseg = PvReallocMsg((struct MSG *)&pos2, cseg * 8, 0x10, aseg);
    ps->cC = cseg;
    func_001D2898(ps->aseg10, aseg, cseg * 8);
    ps->c90 = cpv;
    ps->apv = PvReallocMsg((struct MSG *)&pos2, cpv * 4, 0x10, apv);
    ps->n98 = -1;
}
