// SLY3_CFLAGS: -Os -G0
// Refresh the visible-range list of a sampled path when one of its objects changed: sample the path in steps of 50.0, for each
// position with an object find the surrounding [start, end] range (func_001E7750, 3 = unbounded) and merge it into aseg10, then
// intersect the result with the previous ranges (func_00164D98) and fix up a wrap-around pair. Sly 2 func_001EA000.
typedef int qword __attribute__((mode(TI)));
struct VEC { float x, y, z, w; } __attribute__((aligned(16)));
struct SEG { float a, b; };
struct O { char pad[0xD4]; int fD4; };
struct PV { char pad[0x104]; int n104; };
struct S {
    struct O *po;
    int c4;
    struct SEG *aseg;
    int cC;
    struct SEG aseg10[16];
    int c90;
    struct PV **apv;
    int n98;
};
struct X { char pad[0x40]; float a; float b; char pad2[0x18]; } __attribute__((aligned(16)));
struct G { char pad[0x450C]; int n450C; };
extern struct G D_00475480;
float func_0022DFB0(struct O *);
float func_0022DFD8(struct O *);
void func_0022E330(struct O *, float, qword *, qword *);
void *func_00231C50(qword);
int func_001E7750(void *, struct O *, float, int, qword *, float *);
void *func_00292034(void *, int, unsigned int);
int func_00164D98(int, struct X *, int, struct X *, int, struct X *, int);

void func_00231D00(struct S *ps)
{
    struct VEC pos;
    struct X ax[16];
    struct X ay[16];
    float segStart, segEnd;
    struct SEG *aseg;
    struct SEG *asegSrc;
    int cseg, c, i, j, k, n;
    struct SEG *pseg;
    float tStart, t, tEnd;
    {
        int k;
        for (k = 0; k < ps->c90; k++)
            if (ps->n98 < ps->apv[k]->n104)
                break;
        if (k >= ps->c90)
            return;
    }
    aseg = ps->aseg10;
    cseg = 0;
    tStart = func_0022DFB0(ps->po);
    t = tStart;
    tEnd = func_0022DFD8(ps->po);
    asegSrc = ps->aseg;
    c = ps->c4;
    while (t < tEnd) {
        void *pv;
        func_0022E330(ps->po, t, (qword *)&pos, 0);
        pv = func_00231C50(*(qword *)&pos);
        if (pv) {
            int fSave = ps->po->fD4;
            struct SEG *pseg;
            int fNew;
            int idx;
            ps->po->fD4 = 0;
            if (func_001E7750(pv, ps->po, t, 0, 0, &segStart) == 3)
                segStart = tStart;
            if (func_001E7750(pv, ps->po, t, 1, 0, &segEnd) == 3)
                segEnd = tEnd;
            ps->po->fD4 = fSave;
            pseg = &aseg[cseg];
            fNew = 1;
            while (aseg < pseg) {
                struct SEG *previous = pseg - 1;
                if (previous->b < segStart)
                    break;
                pseg = previous;
                if (pseg->a < segStart) {
                    fNew = 0;
                    break;
                }
            }
            idx = pseg - aseg;
            cseg = idx + 1;
            if (!((unsigned)cseg < 17))
                cseg = idx;
            if (fNew)
                pseg->a = segStart;
            pseg->b = segEnd;
            t = segEnd;
        }
        t += 50.0f;
    }
    for (i = 0; i < c; i++) {
        func_00292034(&ax[i], 0, 0x60);
        ax[i].a = asegSrc[i].a;
        ax[i].b = asegSrc[i].b;
    }
    for (j = 0; j < cseg; j++) {
        func_00292034(&ay[j], 0, 0x60);
        ay[j].a = aseg[j].a;
        ay[j].b = aseg[j].b;
    }
    pseg = ps->aseg10;
    n = func_00164D98(cseg, ay, c, ax, 0x10, ay, 0);
    for (k = 0; k < n; k++) {
        aseg[k].a = ay[k].a;
        aseg[k].b = ay[k].b;
    }
    if (n >= 2 && ps->po->fD4) {
        if (pseg[0].a == tStart && pseg[n - 1].b == tEnd) {
            pseg[0].a = pseg[n - 1].a - tEnd;
            pseg[n - 1].b = pseg[0].b + tEnd;
        }
    }
    ps->cC = n;
    ps->n98 = ++D_00475480.n450C;
}
