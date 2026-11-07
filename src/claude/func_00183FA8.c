// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; void *pfn; };
struct M4 { qword r[4]; };
struct SMPA { float svFast, svSlow, dtFast, sdvMax; };
struct CLQ { float g0, g1, g2; };
struct LO { unsigned char pad0[0xC]; struct VTE *pvt; unsigned char pad10[0x28 - 0x10];
    unsigned long : 56; unsigned long flags : 8; unsigned char pad30[0x130 - 0x30]; int n130; };
struct ELEM { float g; unsigned char pad[0x50 - 4]; };
struct Self {
    unsigned char pad0[0xC]; struct VTE *pvt;
    unsigned char pad10[0x40 - 0x10]; struct LO *plo40;
    unsigned char pad44[0x50 - 0x44]; float g50; struct LO *plo54; float g58; struct LO *plo5C;
    float g60; float g64; struct LO *plo68; int n6C; float g70; float g74; int n78; struct ELEM *aelem;
    int n80; int n84;
};
/* .rodata of the original unit at 0x00321890: two SMPA and the speed curve. */
static const struct SMPA D_00321890 = { 1200.0f, 200.0f, 3.0f, 625.0f };
static const struct SMPA D_003218A0 = { 2000.0f, 700.0f, 1.0f, 1000.0f };
static const struct CLQ D_003218B0 = { 1.0f, -0.3f, 0.0f };
extern float D_0036BB9C;
extern unsigned char D_0036BD20[];
extern unsigned char D_00475480[];
void func_001C8168(struct Self *p);
void func_0022EA88(struct LO *plo, qword pos, int a, int b, int c, int d, float *ps);
int func_0013B500(struct LO *plo, int n);
int func_001A9478(void *p, int n);
float func_0022DFD8(struct LO *plo);
float func_0011E730(float gCur, float dgCur, float gTarget, float dt, const struct SMPA *psmpa, float *pdgNext);
float func_00171C98(void *p);
void func_00184778(struct Self *p);
qword func_00184630(struct Self *p);
int func_0027F258(struct LO *plo, qword q);

static inline qword PosOf(struct LO *p)
{
    struct VTE *e = &p->pvt[36];
    return ((struct M4 *(*)(void *))e->pfn)((char *)p + e->delta)->r[3];
}
static inline float GMax(float a, float b)
{
    return a > b ? a : b;
}


void func_00183FA8(struct Self *p)
{
    int lo, hi, found;
    func_001C8168(p);
    func_0022EA88(p->plo40, PosOf(p->plo5C), 0, 0, 0, 0, &p->g64);
    if (p->n6C) {
        if (func_0013B500(p->plo5C, 0x55) && !func_001A9478(D_00475480, p->plo5C->n130)) {
            if (p->g64 < func_0022DFD8(p->plo40) * 0.67f) {
                int fNear = p->g64 < func_0022DFD8(p->plo40) * 0.33f;
                float dsAhead = fNear ? 2500.0f : 350.0f;
                float dsMin = fNear ? 100.0f : 8.0f;
                /* separate copy of the flag: the first jump-threading pass (before cse) must not see the
                   psmpa test as identical to the dsMin test (the original re-tests it on the near path) */
                int fNearSmpa = fNear;
                const struct SMPA *psmpa = fNearSmpa ? &D_00321890 : &D_003218A0;
                p->g70 = func_0011E730(p->g70, p->g74, GMax(p->g64 + dsAhead, p->g70 + dsMin), D_0036BB9C, psmpa, &p->g74);
            } else {
                float g = func_00171C98(D_0036BD20);
                p->g70 = p->g70 + (D_003218B0.g0 + g * (D_003218B0.g1 + g * D_003218B0.g2)) * p->g58 * D_0036BB9C;
            }
        } else {
            p->g70 = p->g70 + p->g58 * D_0036BB9C;
        }
        if (func_0022DFD8(p->plo40) <= p->g70) {
            func_00184778(p);
            ((void (*)(void *, int, int, int, int, int))p->pvt[3].pfn)((char *)p + p->pvt[3].delta, 5, 0, 0, 0, 0);
        } else {
            qword q = func_00184630(p);
            ((void (*)(void *, qword))p->plo54->pvt[34].pfn)((char *)p->plo54 + p->plo54->pvt[34].delta, q);
            if (p->plo68 && (p->plo68->flags & 1) && func_0027F258(p->plo68, q)) {
                func_00184778(p);
                ((void (*)(void *, int, int, int, int, int))p->pvt[3].pfn)((char *)p + p->pvt[3].delta, 6, 0, 0, 0, 0);
            }
        }
    }
    {
        int n = p->n78;
        lo = 0;
        hi = n - 1;
        found = -1;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            int next = mid + 1;
            struct ELEM *pmid = &p->aelem[mid];
            struct ELEM *pnext = next < n ? &p->aelem[next] : pmid;
            if (pmid->g <= p->g64 && p->g64 <= pnext->g) {
                found = mid;
                goto done;
            }
            if (p->g64 < pmid->g)
                hi = mid - 1;
            else
                lo = next;
        }
    }
done:
    if (found == -1) {
        p->n80 = found;
        p->n84 = -2;
    } else {
        int k = (int)(p->g60 / p->g50);
        p->n80 = found - k < 0 ? 0 : found - k;
        p->n84 = found + k < p->n78 - 1 ? found + k : p->n78 - 1;
    }
}
