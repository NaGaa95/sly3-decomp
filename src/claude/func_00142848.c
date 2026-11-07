// SLY3_CFLAGS: -Os -G0
// A12 draft; A70: dead if/else arms + keep-alive reproduce the orphaned x198 compare.
struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *pvt; };
struct OR { struct O *po; int x4; };
struct P {
    char pad[0x198]; int x198; char pad1[0x298 - 0x19C]; float g298; int x29C; char pad2[0x2FC - 0x2A0];
    void *p2FC; void *p300; void *p304; void *p308; void *p30C; void *p310; char pad3[0x32C - 0x314];
    int c32C; struct O *a330[4]; int c340; struct O *a344[4]; int x354; int x358; float g35C; struct OR aor360[4];
    char pad4[0x38C - 0x380]; float g38C; int x390; int pad394; float g398; int x39C; char pad5[0x3BC - 0x3A0]; float g3BC;
    char pad6[0x428 - 0x3C0]; int x428; char pad7[0x430 - 0x42C]; int x430; char pad8[0x44C - 0x434]; int x44C;
    char pad9[0x4A8 - 0x450]; void *p4A8; char padA[0x4BC - 0x4AC]; int x4BC; char padB[0x4C4 - 0x4C0]; struct O *p4C4;
    char padC[0x4E0 - 0x4C8]; struct O *p4E0; float g4E4;
};
extern struct CLOCK { float t; } g_clock;
extern int D_0047A2B4;
extern const float D_00320074; /* -FLT_MAX (shared literal row 0x320070) */
extern const float D_00320078; /* FLT_MAX */
int func_001F43F0(struct P *p);
void func_001F43D0(struct P *p, int n);
int func_001F4458(struct P *p);
void func_001F4438(struct P *p, int n);
void func_00141FD8(struct P *p, int n);
void func_00137588(void *anim, void *recv, float t, float rate, int flags, void **out);
void func_00142AE0(struct P *p, int n);
void func_00144628(struct P *p, int n);
void func_00143230(struct P *p, int n);
void func_001434A8(struct P *p, int n);
void func_00239FE0(void *p, int n);
static __inline__ void Reset(struct O *po) { po->pvt[9].pfn((char *)po + po->pvt[9].d); }

void func_00142848(struct P *p)
{
    int i;
    unsigned int j = 0;
    struct OR *por = p->aor360;
    float u;
    func_001F43D0(p, func_001F43F0(p));
    func_001F4438(p, func_001F4458(p));
    p->x44C = -1;
    func_00141FD8(p, p->x430);
    u = (float)p->x39C / (float)D_0047A2B4;
    p->g3BC = g_clock.t + u * 0.5f;
    p->g398 = g_clock.t + u * 0.25f;
    p->g38C = g_clock.t + u * 0.25f;
    p->x390 = 0;
    p->g298 = g_clock.t + u * 0.25f;
    p->x29C = 0;
    for (; j < 4; j++, por++) {
        struct O *po = por->po;
        if (po)
            Reset(po);
    }
    func_00137588(p->p2FC, p, 0.0f, 0.0f, 1, &p->p300);
    func_00137588(p->p304, p, 0.0f, 0.0f, 1, &p->p308);
    func_00137588(p->p30C, p, 0.0f, 0.0f, 1, &p->p310);
    func_00142AE0(p, 1);
    func_00144628(p, 0);
    func_00143230(p, 0);
    func_001434A8(p, -1);
    {
        int state = p->x198;
        /* dead arms (A70): flow deletes both sets of i, but the branch and compare survive until jump2 (after
           sched2), so sw x358 is scheduled in the join block like the target */
        if (state < 3) i = p->c340; else i = p->c32C;
        __asm__("" : : "r"(state)); /* zero-insn keep-alive: state stays live past the compare (lw v1 / slti v0) */
    }
    p->x358 = 0;
    p->g35C = D_00320074;
    for (i = 0; i < p->c32C; i++)
        Reset(p->a330[i]);
    for (i = 0; i < p->c340; i++)
        Reset(p->a344[i]);
    if (p->p4A8)
        func_00239FE0(p->p4A8, 0x1A0);
    p->x428 = 0;
    p->x4BC = 0;
    if (p->p4C4)
        Reset(p->p4C4);
    p->g4E4 = D_00320078;
    if (p->p4E0)
        Reset(p->p4E0);
}
