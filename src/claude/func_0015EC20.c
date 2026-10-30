// SLY3_ASFIX: engine-divfix1
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 2 reference: /home/claude/decomp src/hand/func_0014AA30.c.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct RANGE { float a; float b; };
static const struct RANGE D_002BD480 = { 900.0f, 1400.0f };
static const struct RANGE D_002BD488 = { 1400.0f, 4000.0f };
static const struct RANGE D_002BD490 = { 600.0f, 1000.0f };
static const struct RANGE D_002BD498 = { 1000.0f, 4000.0f };
static const struct RANGE D_002BD4A0 = { 0.0f, 10.0f };
extern char D_00475480[];
struct E { int pad[2]; void *x8; };
struct Q { char pad[0xE0]; float *xF0; qword *xF4; };
struct O { char pad[0x40]; int x50; int x54; struct E *x58; struct Q *x5C; };
struct P { char pad[0x38]; struct O *p38; };
struct VEntry { short delta; short pad; void *(*get)(void *); };
struct LO { char pad[0xC]; struct VEntry *table; };
struct LO *func_001F4AD0(void *, int);
void *func_001F4A80(struct LO *);
void func_0022EA88(struct Q *, qword, int, int, int, int, float *);
int func_0011EE30(const struct RANGE *, float);
qword func_001678C8(void *, qword);
float sqrtf(float);

static inline float GRemap(const struct RANGE *pr, float g)
{
    if (pr->a == pr->b)
        return 0.0f;
    return (g - pr->a) / (pr->b - pr->a);
}

int func_0015EC20(struct P *p)
{
    int iBest = -1;
    int i = 0;
    float ag[1];
    struct LO *pv = func_001F4AD0(D_00475480, 0);
    float gBest = -1.0f;
    func_0022EA88(p->p38->x5C, *(qword *)((char *)pv->table[36].get((char *)pv + pv->table[36].delta) + 0x30), 0, 0, 0, 0, ag);
    for (; i < p->p38->x54; i++) {
        float g, u1, u2, u3, s;
        VU v;
        struct E *pe = &p->p38->x58[i];
        if (!pe->x8)
            continue;
        g = ag[0] - p->p38->x5C->xF0[i];
        if (p->p38->x50 == 1)
            g = -g;
        if (func_0011EE30(&D_002BD480, g))
            u1 = GRemap(&D_002BD480, g);
        else if (func_0011EE30(&D_002BD488, g))
            u1 = 1.0f - GRemap(&D_002BD488, g);
        else
            u1 = 0.0f;
        v.q = func_001678C8(func_001F4A80(pv), p->p38->x5C->xF4[i]);
        if (func_0011EE30(&D_002BD490, v.f[2]))
            u2 = GRemap(&D_002BD490, v.f[2]);
        else if (func_0011EE30(&D_002BD498, v.f[2]))
            u2 = 1.0f - GRemap(&D_002BD498, v.f[2]);
        else
            u2 = 0.0f;
        { float l2 = v.f[0] * v.f[0] + v.f[1] * v.f[1]; __asm__ __volatile__("sqrt.s %0, %1" : "=f"(g) : "f"(l2)); }
        if (func_0011EE30(&D_002BD4A0, g))
            u3 = 1.0f - GRemap(&D_002BD4A0, g);
        else
            u3 = 0.0f;
        s = u1 * 0.5f + u2 * 0.15f + u3 * 0.35f;
        if (gBest < s) {
            gBest = s;
            iBest = i;
        }
    }
    return iBest;
}

/* func_0015F050 shares the 16-byte .rodata row at 0x3208C0 (its FLT_MAX literal and jump table) with
   func_0015EC20's RANGE {0,10}, so both functions live in this file. */
// Sly 2 reference: /home/claude/decomp src/hand/func_0014AE38.c (state change of a guard-like controller); Sly 3 spawns
// its actions through a component list at +0x29C and builds the chase action from a ray between two positions.
extern qword D_00317560;
struct CLOCK_F050 { float t; };
extern struct CLOCK_F050 g_clock;
struct V3_F050 { int x; int y; int z; };
struct VTE_F050 { short d; short pad; void *pfn; };
struct LO_F050 { int pad[3]; struct VTE_F050 *vt; };
struct R_F050 { char pad[0x50]; float x50; float x54; };
struct X_F050 {
    int pad[3]; struct VTE_F050 *vt; char pad1[0x1A0 - 0x10]; struct V3_F050 v1A0; char pad2[0x29C - 0x1AC];
    char list29C[0x3AC - 0x29C]; int x3AC; char pad4[0x1080 - 0x3B0]; float x1080;
};
struct P_F050 { char pad[0x10]; struct X_F050 *p10; char pad1[4]; char x18[0x18]; int x30; float x34; char pad2[0x44 - 0x38]; struct R_F050 *p44; };
struct OCA_F050 { int pad[3]; struct VTE_F050 *vt; char pad1[0x38 - 0x10]; void *x38; int x3C; };
struct OF0_F050 { int pad[3]; struct VTE_F050 *vt; char pad1[0x38 - 0x10]; int x38; char pad2[0x44 - 0x3C]; float x44; char pad3[0xB0 - 0x48]; int xB0; char pad4[4]; void *xB8; };
struct OCB_F050 { int pad[3]; struct VTE_F050 *vt; char pad1[0xCC - 0x10]; int xCC; };
struct OD1_F050 { int pad[3]; struct VTE_F050 *vt; char pad1[0x30 - 0x10]; int x30; char pad2[8]; struct R_F050 *x3C; };
void func_002568E8(struct X_F050 *, int, int, qword);
void func_0023EBF8(struct X_F050 *, int);
float func_0011E940(float, float);
void func_00238AE8(void *);
void *func_00238690(void *, int);
struct LO_F050 *func_0015F030(struct P_F050 *);
void *func_001EF038(qword, qword, int);
void func_001D8B40(struct OF0_F050 *, void *);
void func_00132930(struct OCB_F050 *, qword);

#define VCALL0(po, n) { struct VTE_F050 *e = &(po)->vt[n]; ((void (*)(void *))e->pfn)((char *)(po) + e->d); }
#define VCALLQ(po, n, q) { struct VTE_F050 *e = &(po)->vt[n]; ((void (*)(void *, qword))e->pfn)((char *)(po) + e->d, q); }
static inline qword GetPos(struct LO_F050 *o) { return *(qword *)((char *)((void *(*)(void *))o->vt[36].pfn)((char *)o + o->vt[36].d) + 0x30); }

void func_0015F050(struct P_F050 *p, int state)
{
    if (state == p->x30)
        return;
    switch (p->x30) {
    case 0:
        func_002568E8(p->p10, 0, 0, D_00317560);
        break;
    case -1:
    case 1:
        func_0023EBF8(p->p10, 1);
        break;
    case 3: {
        float t = g_clock.t;
        p->p10->x1080 = t + func_0011E940(p->p44->x50, p->p44->x54);
        p->p44 = 0;
        break;
    }
    }
    func_00238AE8(p->x18);
    p->x30 = state;
    p->x34 = g_clock.t;
    switch (state) {
    case 0: {
        struct OCA_F050 *po = func_00238690(p->p10->list29C, 0xCA);
        po->x38 = (void *)func_001F4AD0(D_00475480, 0);
        VCALL0(po, 8);
        VCALLQ(p->p10, 40, D_00317560);
        VCALLQ(p->p10, 41, D_00317560);
        {
            struct V3_F050 *pv = &p->p10->v1A0;
            pv->x = pv->y = pv->z = 0;
        }
        break;
    }
    case 1: {
        qword pos = GetPos((struct LO_F050 *)p->p10);
        void *pray = func_001EF038(pos, GetPos(func_0015F030(p)), 0);
        struct OF0_F050 *po = func_00238690(p->p10->list29C, 0xF0);
        func_001D8B40(po, pray);
        po->xB0 = 0xD;
        po->x38 = 1;
        po->x44 = 25.0f;
        po->xB8 = (void *)func_001F4AD0(D_00475480, 0);
        VCALL0(po, 8);
        p->p10->x1080 = g_clock.t;
        func_0023EBF8(p->p10, 0);
        break;
    }
    case 2: {
        struct OCB_F050 *po = func_00238690(p->p10->list29C, 0xCB);
        func_00132930(po, GetPos(func_0015F030(p)));
        po->xCC = 1;
        VCALL0(po, 8);
        break;
    }
    case 3: {
        struct OD1_F050 *po = func_00238690(p->p10->list29C, 0xD1);
        po->x30 = p->p10->x3AC;
        po->x3C = p->p44;
        VCALL0(po, 8);
        p->p10->x1080 = 3.40282346638528859812e+38f;
        break;
    }
    case 4: {
        struct OCA_F050 *po = func_00238690(p->p10->list29C, 0xCA);
        po->x38 = (void *)func_001F4AD0(D_00475480, 0);
        po->x3C = 1;
        VCALL0(po, 8);
        break;
    }
    case -1:
        func_0023EBF8(p->p10, 0);
        break;
    }
}
/* Next .rodata item of the original unit: the identifier table {50,51,52,53} read by func_0015F3D8
   (src/engine/init_session_15f3d8.c, matched separately); it follows the jump table at 0x3208E8. */
const int D_003208E8[4] = { 50, 51, 52, 53 };
