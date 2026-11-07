// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly3 InitStepguard (cf Sly2 InitStepguard__FP9STEPGUARD 0x205EB8); store order hill-climbed.
struct F3C { char pad[0x3C]; int u3C; };
struct V3 { float x, y, z; };
struct S {
    char pad0[0x120]; unsigned long b_lo : 48; unsigned long b_f : 4; unsigned long b_hi : 12;
    char p1[0x290 - 0x128]; float f290;
    char p2[0x308 - 0x294]; float f308; float f30C;
    char p3[0x344 - 0x310]; float f344, f348, f34C, f350, f354, f358;
    char p4[0x370 - 0x35C]; int n370, n374, n378, p37C; float f380; int n384; char p5[0x390 - 0x388];
    float f390, f394, f398; int n39C; float f3A0, f3A4, f3A8;
    char p6[0x3E4 - 0x3AC]; int n3E4; char p7[0x400 - 0x3E8]; int n400; char p8[0x40C - 0x404]; int n40C;
    char p9[0x1004 - 0x410]; int n1004, n1008; float f100C, f1010; char pA[0x1018 - 0x1014]; int n1018;
    float f101C, f1020; int n1024; char pB[0x10AC - 0x1028]; int n10AC; char pC[0x10B4 - 0x10B0];
    float f10B4, f10B8, f10BC, f10C0, f10C4, f10C8; char pD[0x10D0 - 0x10CC]; struct F3C *p10D0;
    char pE[0x10F0 - 0x10D4]; int n10F0; char pF[0x112C - 0x10F4]; int n112C; char pG[0x1150 - 0x1130]; float f1150;
    char pH[0x1160 - 0x1154]; int n1160; char pI[0x1174 - 0x1164]; float f1174, f1178, f117C, f1180, f1184, f1188, f118C;
    char pJ[0x11A0 - 0x1190]; struct V3 v11A0; char pK[0x11B0 - 0x11AC]; float f11B0, f11B4; char pL[0x11C0 - 0x11B8];
    int n11C0; char pM[0x11E0 - 0x11C4]; float f11E0;
};
static inline void SetYZ(struct V3 *pv, float y, float z) { pv->y = y; pv->z = z; }
void func_0024D8A8(struct S *p);
void func_00250820(void);
struct F3C *func_00150690(int a, void *b, int c, int d);
void func_001C9118(struct F3C *p, int n);
void func_002539A0(struct S *p);

void func_00250868(struct S *p)
{
    int v;
    float a, b, limit, medium, high, extent;
    func_0024D8A8(p);
    func_00250820();
    p->p10D0 = func_00150690(0xF, 0, 0x2F5, -1);
    func_001C9118(p->p10D0, 2);
    v = p->p10D0->u3C;
    if ((v ^ 1) & 1)
        *(int *)v &= -3;
    else
        p->p10D0->u3C = v & -3;
    a = 0.785398245f; b = 1.30899704f; limit = 3.40282346638528859812e+38f; medium = 300.0f; high = 1200.0f; extent = 800.0f;
    p->f10BC = -a;
    p->f10C0 = a;
    p->f10C4 = -b;
    p->f10B4 = medium;
    p->f10C8 = b;
    p->f10B8 = high;
    p->f344 = extent;
    p->f34C = medium;
    p->f348 = high;
    p->f350 = 450.0f;
    p->f354 = medium;
    p->f358 = 600.0f;
    p->f308 = limit;
    p->f30C = limit;
    p->f390 = -100.0f;
    p->f394 = 350.0f;
    p->f398 = 1000.0f;
    p->f3A0 = -800.0f;
    p->f3A4 = extent;
    p->f3A8 = 3000.0f;
    p->n384 = 1;
    p->f101C = 16.0f;
    p->f1020 = 20.0f;
    p->n1024 = 50;
    p->f100C = 5.5f;
    p->f1010 = 6.5f;
    p->n1018 = 0;
    p->n39C = 1;
    p->n1004 = 1;
    p->n10AC = 1;
    p->n1008 = -1;
    p->n374 = 0x229FF7E;
    p->n370 = 0x20F800;
    p->f380 = -10.0f;
    p->n378 = 0xF800;
    p->n3E4 = -1;
    p->f290 = 1.5f;
    p->b_f = 2;
    p->n400 = -200;
    p->n10F0 = -1;
    p->n40C = -1;
    p->n112C = -1;
    p->f1150 = -3.40282346638528859812e+38f;
    p->n11C0 = 0;
    p->f11E0 = 1.0f;
    p->f1184 = 1300.0f;
    p->f1188 = -500.0f;
    p->f118C = 500.0f;
    p->f1178 = 600.0f;
    p->f117C = -300.0f;
    p->f1180 = 300.0f;
    p->f1174 = 7.0f;
    p->v11A0.x = 2.35f;
    p->n1160 = 0;
    SetYZ(&p->v11A0, -0.67f, 0.02f);
    p->f11B0 = 1.75f;
    p->f11B4 = 2.15f;
    func_002539A0(p);
}
/* next literal of this unit's .rodata block (used by func_00251000) */
extern const float D_00327298 = -3.40282346638528859812e+38f;
