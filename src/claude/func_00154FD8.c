// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef struct SMP { float gA; float gB; float gC; } SMP;
struct L { char pad[0x104]; float g104; };
struct P {
    char pad[0x2C]; unsigned char b2C; char pad1[0x70 - 0x2D]; char light[0x104 - 0x70]; float g104; int pad108; void *p10C;
    char pad2[0x508 - 0x110]; int x508; char pad3[0xF64 - 0x50C]; int xF64; char pad4[0xF78 - 0xF68]; int xF78;
    char pad5[0x11AC - 0xF7C]; float g11AC; float g11B0; char pad6[0x15F8 - 0x11B4]; int x15F8;
    char pad7[0x1AA0 - 0x15FC]; struct L *p1AA0; struct L *p1AA4; char pad8[0x1F1C - 0x1AA8]; int x1F1C;
};
extern struct CLOCK { float t; float dt; } g_clock;
extern int D_00479284;
extern struct P *D_00370AC0;
extern struct P *D_0046FF30;
extern qword D_00479350;
static const SMP s_smp = { 12.0f, 2.0f, 0.1f };
void func_0023CBE0(void);
/* GSmooth; arguments in Sly 2 order (gCur, gTarget, dt, psmp, pdgNext) - same registers, the order fixes scheduling */
float func_0011E598(float gCur, float gTarget, float dt, const SMP *psmp, float *pdgNext);
void func_0018E800(void *light, qword color, void *matrix, float scale, float intensity, void *payload);

void func_00154FD8(struct P *p)
{
    float gA, gB, s;
    if (!(p->b2C & D_00479284))
        return;
    func_0023CBE0();
    if (p->xF64 == 1 && p->xF78 != 2)
        return;
    if (p->x508 == 2 || (p == D_00370AC0 && p->x1F1C)) {
        gA = 0.15f;
        gB = 0.0f;
    } else if (p == D_0046FF30 && p->x15F8) {
        gB = 0.0f;
        gA = gB;
    } else {
        gB = 1.0f;
        gA = gB;
    }
    p->g11AC = func_0011E598(p->g11AC, gA, g_clock.dt, &s_smp, 0);
    p->g11B0 = func_0011E598(p->g11B0, gB, g_clock.dt, &s_smp, 0);
    if (p == D_0046FF30 && p->g11AC < 0.1f)
        return;
    if (p == D_00370AC0) {
        p->p1AA0->g104 = p->g11AC;
        p->p1AA4->g104 = p->g11AC;
    }
    s = p->g104;
    func_0018E800(p->light, D_00479350, 0, s * p->g11AC, s * p->g11B0, p->p10C);
}
/* Next .rodata item of the original unit (the FLT_MAX literal read by a later function); it follows s_smp. */
const float D_003205AC = 3.402823466e+38f;
