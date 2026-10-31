// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct OBJ { char pad[0xC]; struct VTE *pvt; };
struct ACT { char pad[0x2C]; struct VTE *pvt; };
struct P {
    char pad0[0xC]; struct VTE *pvt; char pad10[0x134 - 0x10]; struct ACT *p134; char pad138[0x2B0 - 0x138]; int x2B0;
    char pad2B4[0x430 - 0x2B4]; int x430; int pad434; int state; float t43C; int x440; int x444; char pad448[0x450 - 0x448];
    char x450[8]; int x458; char pad45C[0x478 - 0x45C]; void *x478; char pad47C[0x480 - 0x47C]; struct OBJ *p480; void *p484;
    void *x488; void *x48C; void *x490; void *x494; void *x498; void *x49C; void *x4A0; char pad4A4[0x4A8 - 0x4A4]; void *p4A8;
    char pad4AC[0x4B4 - 0x4AC]; float t4B4; float t4B8;
};
struct M4 { qword r[4]; };
struct CLOCK { float t; };
extern struct CLOCK g_clock;
extern qword D_00317560;
void func_00141FD8(struct P *p, int st);
void func_00142650(struct P *p);
qword func_00142D20(struct P *p);
int func_00145080(struct P *p, void *a, void *b, qword *pv, float g);
void func_00162148(void *p);
void func_00162698(void *p, int n);
void func_001C7A00(struct OBJ *p, int a, int b);
struct OBJ *func_001FBE30(void *p, int n);
void func_001FE728(void *p, int n);
void func_00239CE8(void *p, int n);
int func_00239E70(void *p);
void func_0023EBF8(struct OBJ *p, int n);
void func_0023EC98(struct OBJ *p, int n);
#define VCALL(o, n, T) ((T)(o)->pvt[n].pfn)((char *)(o) + (o)->pvt[n].d

void func_001421C0(struct P *p)
{
    int fOk;
    void *pvA;
    void *pvB;
    void *pvC;
    float g;
    qword v;
    if (p->state == -1) {
        if (p->x430 == -1)
            return;
        func_00141FD8(p, p->x430);
    }
    if (p->x440 >= p->x444 && p->state != p->x430)
        return;
    switch (p->x2B0) {
    case 2: case 3: case 4: case 5:
        return;
    }
    func_00162148(p->x450);
    {
        int f = 1;
        if (p->state == 0x3C && p->t4B4 > p->t43C)
            f = 0;
        if (f) {
            if (!VCALL(p->p134, 1, int (*)(void *, int, float)), 4, 0.0f))
                return;
        }
    }
    fOk = 0;
    switch (p->state) {
    case 0x36:
        fOk = p->x488 != 0;
        break;
    case 0x37:
        fOk = p->x48C != 0;
        break;
    case 0x38:
        fOk = p->x490 != 0;
        break;
    case 0x39:
        fOk = p->p4A8 && func_00239E70(p->p4A8) == 0x1A0;
        break;
    case 0x3A:
        fOk = p->x494 != 0;
        break;
    case 0x3B:
        fOk = p->x498 != 0;
        break;
    case 0x3C:
        fOk = p->x49C && g_clock.t - p->t4B8 > 0.25f;
        break;
    case 0x3D:
        fOk = p->x4A0 != 0;
        break;
    }
    if (!fOk)
        return;
    pvA = 0;
    pvC = 0;
    if (p->x458 == 2) {
        pvB = p->x478;
        v = D_00317560;
    } else {
        pvB = 0;
        v = func_00142D20(p);
    }
    switch (p->state) {
    case 0x36:
        g = 2.5f;
        pvA = p->x488;
        break;
    case 0x37:
        g = 2.5f;
        pvA = p->x48C;
        break;
    case 0x38:
        pvA = p->x490;
        g = 3.0f;
        break;
    case 0x39:
        if (p->p4A8)
            func_00239CE8(p->p4A8, 0x1A1);
        break;
    case 0x3A:
        pvC = p->x494;
        break;
    case 0x3B:
        pvA = p->x498;
        g = 3.0f;
        break;
    case 0x3C:
        if (p->t4B4 < p->t43C)
            p->t4B4 = g_clock.t;
        pvC = g_clock.t - p->t4B4 < 5.0f ? p->x49C : 0;
        break;
    case 0x3D:
        pvA = p->x4A0;
        g = 3.0f;
        break;
    }
    if (pvA) {
        if (!func_00145080(p, pvA, pvB, &v, g))
            return;
    } else if (pvC) {
        struct OBJ *po;
        if (!p->p480)
            return;
        po = func_001FBE30(pvC, 0);
        if (po) {
            func_001C7A00(po, 0, 0);
            {
                struct VTE *e = &po->pvt[34];
                char *self = (char *)po + e->d;
                ((void (*)(void *, qword))e->pfn)(self, VCALL(p->p480, 36, struct M4 *(*)(void *)))->r[3]);
            }
            VCALL(po, 40, void (*)(void *, qword)), D_00317560);
            VCALL(po, 41, void (*)(void *, qword)), D_00317560);
            func_0023EBF8(po, 1);
            func_0023EC98(po, 1);
            if (p->p484)
                func_001FE728(p->p484, 1);
        } else if (p->state != 0x3C) {
            return;
        }
    }
    VCALL(p->p134, 2, void (*)(void *, int)), 4);
    if (p->x458 != -1)
        func_00162698(p->x450, 0);
    if (p->state == 0x3C) {
        p->t4B8 = g_clock.t;
        if (pvC)
            return;
    }
    if (p->state != p->x430)
        p->x440++;
    func_00142650(p);
    if (p->x440 >= p->x444)
        func_00141FD8(p, p->x430);
}
