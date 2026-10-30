// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Script builtin (Sly 2 func_001249A8 evolved): ray-cast aref[1]->aref[2] against every SO of each LO in list aref[0].
   pv == 0x83: list of (lo pos normal) for every hit; pv == 0x84: (lo pos) of the nearest hit. */
typedef int qword __attribute__((mode(TI)));
struct NODE;
struct LO;
struct CRef {
    short m_tagk; short m_cref; union { int n; float g; void *pv; NODE *pnode; qword *pq; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(NODE *pn) __asm__("func_0012B6C8");
    CRef &operator=(void *pv);
    CRef &operator=(qword *pv) __asm__("func_0012B400");
    CRef &operator=(qword v) __asm__("func_0012B470");
};
extern "C" {
NODE *func_002BA6B8();
void func_002BA840(NODE *, int);
}
struct SPM {
    NODE *p;
    void operator=(NODE *pn) __asm__("func_002BA780");
};
struct NODE {
    CRef ref;
    int x8;
    SPM pnext;
};
struct SPN {
    NODE *p;
    void Set(NODE *pn) __asm__("func_002BA760");
    SPN(NODE *pn) { Set(pn); }
    ~SPN() { NODE *pn = p; if (pn && --pn->ref.m_cref == 0) func_002BA840(pn, 3); }
    void operator=(NODE *pn) __asm__("func_002BA780");
    NODE *operator->() { return p; }
    int pad[3];
};
struct SO {
    char pad[0x18];
    unsigned long grf;
    char pad20[0xD0 - 0x20];
};
struct LO {
    char pad[0xD0];
    int cso;
    SO *aso;
};
struct HIT {
    qword pos;
    qword normal;
    char pad[0x40 - 0x20];
    float s;
    char pad44[0x60 - 0x44];
};
extern "C" int func_00164A10(SO *pso, qword pos0, qword pos1, int f, HIT *phit);

extern "C" CRef func_001269D8(int pv, int c, CRef *aref)
{
    CRef ref;
    if (aref[0].m_tagk == 0) {
        ref = aref[0];
    } else {
        SPN spHead(0);
        LO *ploBest = 0;
        SPN spTail(0);
        float sMin = 3.402823466e+38f;
        qword posBest;
        NODE *pn;

        for (pn = aref[0].u.pnode; pn; pn = pn->pnext.p) {
            LO *plo = (LO *)pn->ref.u.pv;
            int i;
            if (!plo)
                continue;
            for (i = 0; i < plo->cso; i++) {
                SO *pso = &plo->aso[i];
                HIT hit;
                if (pso->grf & 0x80000)
                    continue;
                if (func_00164A10(pso, *aref[1].u.pq, *aref[2].u.pq, 1, &hit) <= 0)
                    continue;
                if (pv == 0x83) {
                    SPN spLo(func_002BA6B8());
                    SPN spPos(func_002BA6B8());
                    SPN spNormal(func_002BA6B8());
                    SPN spItem(func_002BA6B8());
                    spLo->ref = (void *)plo;
                    spLo->pnext = spPos.p;
                    spPos->ref = &hit.pos;
                    spPos->pnext = spNormal.p;
                    spNormal->ref = &hit.normal;
                    spItem->ref = spLo.p;
                    if (spHead.p)
                        spTail->pnext = spItem.p;
                    else
                        spHead = spItem.p;
                    spTail = spItem.p;
                } else if (hit.s < sMin) {
                    posBest = hit.pos;
                    sMin = hit.s;
                    ploBest = plo;
                }
            }
        }
        if (pv == 0x84 && ploBest) {
            SPN spLo(func_002BA6B8());
            SPN spPos(func_002BA6B8());
            spLo->ref = (void *)ploBest;
            spLo->pnext = spPos.p;
            spPos->ref = posBest;
            spHead = spLo.p;
        }
        if (spHead.p)
            ref = spHead.p;
        else
            ref.m_tagk = 0;
    }
    return ref;
}
