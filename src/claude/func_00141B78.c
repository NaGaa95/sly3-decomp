// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct OBJ { char pad[0xC]; struct VTE *pvt; };
struct LO1E8 { char pad[0x14]; void *p14; };
struct SRC { char pad[0x1E8]; struct LO1E8 *p1E8; };
struct DZ {
    char pad0[0x14]; struct SRC *pso; char pad18[0x20 - 0x18]; int k; int x24; int x28; char pad2C[0x30 - 0x2C]; qword v30;
    char pad40[0x50 - 0x40]; int grf;
};
struct P {
    char pad0[0xC]; struct VTE *pvt; char pad10[0x14 - 0x10]; void *p14; char pad18[0x130 - 0x18]; int x130;
    char pad134[0x198 - 0x134]; int x198; char pad19C[0x208 - 0x19C]; int x208; char pad20C[0x214 - 0x20C]; int x214;
    char pad218[0x238 - 0x218]; void *p238; char pad23C[0x2B0 - 0x23C]; int x2B0; char pad2B4[0x380 - 0x2B4]; struct OBJ *p380;
    char pad384[0x430 - 0x384]; int x430; char pad434[0x478 - 0x434]; void *p478; char pad47C[0x4A8 - 0x47C];
    void *p4A8; void *p4AC; float g4B0; char pad4B4[0x4BC - 0x4B4]; void *p4BC; float g4C0; struct OBJ *p4C4;
    char ab4C8[0x10]; int x4D8; char ab4DC[4]; struct OBJ *p4E0; float g4E4; char ab4E8[0x10]; int x4F8; char ab4FC[4];
};
struct CLOCK { float t; };
extern struct CLOCK g_clock;
extern const float D_00320008;
extern char D_0036E740[][0x11C0];
extern char D_0036C700[];
int func_00239E70(void *p);
void func_001FE728(void *p, int n);
int func_0013B500(void *p, int n);
void func_001F4DD8(struct P *p, void *pso, float g, int k);
void func_00147278(struct P *p, int n, void *a, void *b);
void func_00141FD8(struct P *p, int n);
void func_001F4438(struct P *p, int n);
void func_001F43D0(struct P *p, int n);
int func_001F43C8(struct P *p);
void func_00136908(void *p, int a, float f, float g, int b, int c);
void func_00145F70(struct P *p, qword v);
void func_001A9058(void *p, int n, float g);
void *func_001F4A80(struct P *p);
void func_00167D38(void *p, int n);
void func_00142AE0(struct P *p, int n);
void func_001854C8(void *p, int n, struct P *q);
#define VCALL(o, n, T) ((T)(o)->pvt[n].pfn)((char *)(o) + (o)->pvt[n].d

int func_00141B78(struct P *p, struct DZ *pdz)
{
    switch (p->x2B0) {
    case 2:
    case 5:
        return 0;
    case 4: {
        int f = !p->x198 && p->x208;
        if (f)
            return 0;
        break;
    }
    }
    if (!(pdz->grf & 2))
        return 0;
    if (VCALL(p, 80, int (*)(void *, int)), pdz->k))
        return 0;
    if (p->p4A8 && func_00239E70(p->p4A8) != 0x1A0) {
        if (p->p4AC) {
            if (g_clock.t - p->g4B0 > 0.5f) {
                p->g4B0 = g_clock.t;
                func_001FE728(p->p4AC, 1);
            }
        }
        return 0;
    }
    if (func_0013B500(pdz->pso, 0x59) && pdz->pso->p1E8->p14 == p->p14 && !pdz->x28)
        return 0;
    func_001F4DD8(p, pdz->pso, D_00320008, pdz->k);
    switch (pdz->k) {
    case 0x10000:
        if (p->p4E0) {
            VCALL(p->p4E0, 8, void (*)(void *)));
            p->g4E4 = g_clock.t;
        }
        func_00147278(p, p->x4F8, p->ab4E8, p->ab4FC);
        func_00141FD8(p, p->x430);
        func_001F4438(p, 0);
        return 1;
    case 0x800000:
        if (p->p478 && func_0013B500(p->p478, 0x52)) {
            func_00147278(p, p->x4D8, p->ab4C8, p->ab4DC);
            if (p->p4C4)
                VCALL(p->p4C4, 8, void (*)(void *)));
            p->p4BC = p->p478;
            p->g4C0 = g_clock.t;
            return 1;
        }
        break;
    }
    if (pdz->x28)
        func_001F43D0(p, 0);
    else
        func_001F43D0(p, func_001F43C8(p) - pdz->x24);
    if (p->p238)
        func_00136908(p->p238, p->x214, 0.0f, 1.0f, 1, 0);
    func_00145F70(p, pdz->v30);
    if (!p->x198 && p->x130 != -1) {
        func_001A9058(D_0036E740[p->x130], 4, 0.75f);
        func_00167D38(func_001F4A80(p), 0);
    }
    {
        int fSelf = pdz->pso == (struct SRC *)p && pdz->k == 0x200;
        if (func_001F43C8(p) > 0) {
            if (fSelf) {
                if (p->p380) {
                    VCALL(p->p380, 34, void (*)(void *, qword)), pdz->v30);
                    func_001FE728(p->p380, 1);
                }
                func_00142AE0(p, 4);
            }
            if (!p->x198)
                func_001854C8(D_0036C700, 0xA, p);
            return 1;
        }
    }
    func_00142AE0(p, 5);
    return 1;
}
