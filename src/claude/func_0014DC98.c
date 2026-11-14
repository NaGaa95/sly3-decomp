// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Sly 3 version of Sly 2 src/hand/func_0013C560.c (state change). Case-2 LINKE positions in locals + zero-instruction "j"(qb) asm. Owns rodata 0x320300 (vector) + jump tables 0x320310/0x320340. */
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(); };
struct VT { struct VTE a[64]; };
struct M4 { qword r[4]; };
struct CLOCK { float t; float dt; };
struct GS { char pad[0x4E4C]; void *p4E4C; };
struct ST { char pad[0xC]; int xC; char pad1[0x18 - 0x10]; int x18; int c1C; int a20[1]; };
struct SA0 { int x0; int x4; float g8; };
struct E {
    char pad[0x18]; float g18; void *p1C; char pad1[0xA0 - 0x20]; struct SA0 sA0;
    char pad2[0xE8 - 0xAC]; struct VT *pvt; char pad3[0x104 - 0xEC]; void *p104;
};
struct O;
struct Q { char pad[0xC]; struct VT *pvt; int x10; char pad1[0x19C - 0x14]; float g19C; char pad2[0x1A4 - 0x1A0]; struct O *p1A4; char a1A8[4]; };
struct R { char pad[0xC]; struct VT *pvt; };
struct OT { char pad[0x1278]; struct R *pr; struct O *p127C; };
struct O {
    char pad[0xC]; struct VT *pvt; char pad1[0xD0 - 0x10]; int cD0; char *aD4;
    char pad2[0x138 - 0xD8]; struct ST *pst; struct Q *pq; struct OT *pot; int x144;
    char pad3[0x160 - 0x148]; float g160; int st; float g168; struct E *pe;
};
extern struct CLOCK g_clock;
extern struct GS D_00475480;
extern char D_0036C700[];
extern qword D_00317560;
static const float RO_00320300[4] = { 0.0f, 0.0f, -2500.0f, 0.0f };
int func_0014DC88(int st);
void func_001FC090(void *pv, struct O *p);
void func_001FC060(void *pv, struct O *p);
void func_0023FFA0(struct O *p);
void func_0023FE38(struct O *p, int n);
void func_0023B978(struct O *p, void *pv);
void func_00240080(struct O *p, int n);
void func_00240000(struct O *p, int n);
void func_00173EE8(struct GS *pgs, int n, qword v, struct Q *pq, void *pv);
void func_001854C8(void *pv, int n, struct O *p);
void func_0014E770(struct O *p, float g);
void func_0025D940(struct GS *pgs, int n, int m, struct O *pa, struct O *pb, float g);
void func_0023EBF8(struct O *p, int n);
void func_0023EC98(struct O *p, int n);
void func_0023ED58(struct O *p, qword v);
void func_001C7A00(struct O *p, void *pv, int n);
void func_0023D938(struct O *p, qword v);
void func_0023D9D0(struct O *p, qword v);
void func_00241338(struct O *p, float g);
struct E *func_0020B9C0(struct GS *pgs, int n, int m);
void func_0020C6C8(struct E *pe, struct O *p);
void func_0020D3A0(struct E *pe);
float func_0011E940(float a, float b);
void func_0014DC98(struct O *p, int st);

#define VCALL(po, slot, T) ((T)(po)->pvt->a[slot].pfn)((char *)(po) + (po)->pvt->a[slot].d
typedef void (*PFN3)(void *, int, int, int, int, int);
typedef void (*PFNV)(void *);
typedef void (*PFNQ)(void *, qword);
typedef struct M4 *(*PFNM)(void *);
typedef void (*PFNP)(void *, int, struct M4 *);
typedef void (*PFNE)(void *, qword, float);
#define VCALL43(po, M) { struct VTE *pvte = &(po)->pvt->a[43]; ((PFNP)pvte->pfn)((char *)(po) + pvte->d, 0, M); }
#define MATRIX(po) (VCALL(po, 36, PFNM)))

static inline float Dist(qword a, qword b)
{
    qword d;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x $vf2, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, $vf2, %0z"
        : "+j"(d) : : "vf2");
    __asm__("vsqrt Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}

static inline qword Pos(void *po) { return MATRIX((struct R *)po)->r[3]; }
static inline float Dist3(qword a, qword b, float k)
{
    qword d;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x $vf2, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, $vf2, %0z"
        : "+j"(d) : : "vf2");
    __asm__("vsqrt Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "+j"(d));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(d), "f"(k));
    return g;
}
static inline float GMax(float a, float b) { return a < b ? b : a; }

#define LINKE(PE, PA, PB) { \
    struct VTE *pvte = &(PE)->pvt->a[1]; \
    float g; \
    ((PFNE)pvte->pfn)((char *)(PE) + pvte->d, Pos(PA), 1.0f); \
    func_0020C6C8(p->pe, p); \
    { qword qa = Pos(PA); qword qb = Pos(PB); __asm__("" : : "j"(qb)); /* zero-instruction use: gives pos2 a REG_DEAD here so local-alloc ranks it after pos1 (pos1 vf1) */ g = Dist(qa, qb); } \
    p->pe->p1C = (PB); \
    p->pe->g18 = GMax(250.0f, g) * 0.002f; \
    { struct SA0 *ps = &p->pe->sA0; ps->x0 = 0; ps->g8 = -3000.0f; ps->x4 = 0; } \
    p->pe->p104 = (PA); \
    func_0020D3A0(p->pe); \
    VCALL(p, 8, PFNV)); \
}
#define LINKE3(PE, PA, PB) { \
    struct VTE *pvte = &(PE)->pvt->a[1]; \
    float g; \
    ((PFNE)pvte->pfn)((char *)(PE) + pvte->d, Pos(PA), 1.0f); \
    func_0020C6C8(p->pe, p); \
    g = Dist3(Pos(PA), Pos(PB), 250.0f); \
    p->pe->p1C = (PB); \
    p->pe->g18 = GMax(250.0f, g) * 0.002f; \
    { struct SA0 *ps = &p->pe->sA0; ps->x0 = 0; ps->g8 = -3000.0f; ps->x4 = 0; } \
    p->pe->p104 = (PA); \
    func_0020D3A0(p->pe); \
    VCALL(p, 8, PFNV)); \
}

void func_0014DC98(struct O *p, int st)
{
    int stOld;
    struct OT *pot;
    int i;

    if (p->st == st)
        return;
    if (D_00475480.p4E4C != 0) {
        int fOld = func_0014DC88(p->st);
        int fNew = func_0014DC88(st);
        if (fOld) {
            if (!fNew)
                func_001FC090(D_00475480.p4E4C, p);
        } else if (fNew) {
            func_001FC060(D_00475480.p4E4C, p);
        }
    }
    stOld = p->st;
    pot = p->pot;
    switch (stOld) {
    case -1:
        break;
    case 0:
        func_0023FFA0(p);
        for (i = 0; i < p->pst->c1C; i++)
            func_0023FE38(p, p->pst->a20[i]);
        for (i = 0; i < p->cD0; i++)
            func_0023B978(p, p->aD4 + i * 0xD0);
        break;
    case 1: {
        float g;
        if (p->pst->x18 != -1)
            func_00240080(p, p->pst->x18);
        func_00173EE8(&D_00475480, 1, MATRIX(p->pq)->r[3], p->pq, p->pq->a1A8);
        VCALL(p->pq, 3, PFN3), 10, 0, 0, 0, 0);
        {
            struct Q *pq = p->pq;
            pq->p1A4 = 0;
            g = pq->g19C;
        }
        p->pq = 0;
        VCALL(p, 3, PFN3), 5, 0, 0, 0, 0);
        if (st == 2) {
            func_001854C8(D_0036C700, 0x41, p);
            func_0014E770(p, g_clock.t + g);
        }
        break;
    }
    case 2:
        p->pe = 0;
        if (st == 4)
            p->g160 = 0.3f;
        break;
    case 3:
        p->pe = 0;
        break;
    case 4:
        p->pot = 0;
        VCALL(pot->pr, 9, PFNV));
        pot->p127C = 0;
        if (p->pst->xC && st == 7) {
            func_001854C8(D_0036C700, 0x44, p);
            func_0014E770(p, g_clock.t + 10.0f);
        }
        break;
    case 5:
        func_0025D940(&D_00475480, p->x144, -1, p, p, 1.0f);
        func_0023EBF8(p, 1);
        func_0023EC98(p, 1);
        VCALL(p, 40, PFNQ), D_00317560);
        VCALL(p, 41, PFNQ), D_00317560);
        func_0023ED58(p, D_00317560);
        if (p->pst->x18 != -1)
            func_00240080(p, p->pst->x18);
        break;
    case 6:
        p->g160 = 0.0f;
        break;
    case 7:
        break;
    }

    p->st = st;
    p->g168 = g_clock.t;

    switch (st) {
    case 0:
        p->pst = 0;
        func_001C7A00(p, 0, 0);
        VCALL(p, 9, PFNV));
        break;
    case 1:
        if (p->pst->x18 != -1)
            func_00240000(p, p->pst->x18);
        func_00173EE8(&D_00475480, -1, D_00317560, 0, p->pq->a1A8);
        VCALL43(p, MATRIX(p->pq))
        func_001C7A00(p, (void *)p->pq->x10, 3);
        p->pq->p1A4 = p;
        func_0023D938(p, D_00317560);
        func_0023D9D0(p, D_00317560);
        if (stOld != 3) {
            VCALL(p, 9, PFNV));
            func_00241338(p, 0.5f);
        }
        VCALL(p, 3, PFN3), 6, 0, 0, 0, 0);
        VCALL(p->pq, 3, PFN3), 11, 0, 0, 0, 0);
        if (stOld == 3)
            func_001854C8(D_0036C700, 0x42, 0);
        break;
    case 2:
    case 6:
        VCALL(p->pot->pr, 8, PFNV));
        if (p->st == 2) {
            p->pe = func_0020B9C0(&D_00475480, 5, 0);
        } else {
            p->pe = 0;
            VCALL(p, 3, PFN3), 6, 0, 0, 0, 0);
            VCALL(p, 3, PFN3), 5, 0, 0, 0, 0);
        }
        if (p->pe)
            LINKE(p->pe, p, p->pot->pr);
        VCALL43(p, MATRIX(p->pot->pr))
        func_001C7A00(p, p->pot->pr, 3);
        func_0023D938(p, D_00317560);
        func_0023D9D0(p, D_00317560);
        if (!p->pe)
            func_0014DC98(p, 4);
        break;
    case 3:
        VCALL43(p, MATRIX(p->pq))
        func_001C7A00(p, (void *)p->pq->x10, 3);
        func_0023D938(p, D_00317560);
        func_0023D9D0(p, D_00317560);
        p->pe = func_0020B9C0(&D_00475480, 5, 0);
        if (p->pe)
            LINKE3(p->pe, pot->pr, p);
        if (!p->pe)
            func_0014DC98(p, 1);
        break;
    case 4:
        p->pot->p127C = p;
        break;
    case 7:
        break;
    case 5: {
        union { qword q; float f[4]; } v;
        union { qword q; float f[4]; } u;
        union { qword q; float f[4]; } s;
        float a, b, c;
        float lo, hi;
        if (p->pst->x18 != -1)
            func_00240000(p, p->pst->x18);
        lo = -6.2831855f;
        func_001C7A00(p, 0, 3);
        hi = 6.2831855f;
        func_0023EBF8(p, 0);
        func_0023EC98(p, 0);
        {
            qword *pv = MATRIX(p)->r;
            qword vv = *pv;
            struct VT *pvt;
            qword sq, vq;
            __asm__("qmtc2.ni %1, %0" : "=j"(sq) : "r"(1000.0f));
            pvt = p->pvt;
            __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(vq) : "j"(vv), "j"(sq), "r"(pvt));
            s.q = sq;
            v.q = vq;
            ((PFNQ)pvt->a[40].pfn)((char *)p + pvt->a[40].d, v.q);
        }
        a = func_0011E940(lo, hi);
        b = func_0011E940(lo, hi);
        c = func_0011E940(lo, hi);
        u.f[0] = a;
        u.f[1] = b;
        u.f[2] = c;
        VCALL(p, 41, PFNQ), u.q);
        func_0023ED58(p, *(qword *)RO_00320300);
        func_001854C8(D_0036C700, 0x43, p);
        break;
    }
    }
}
