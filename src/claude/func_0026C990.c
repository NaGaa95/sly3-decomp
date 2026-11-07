// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VTE { short d; short pad; int (*pfn)(void *, int); };
struct VT { char pad[0x280]; struct VTE e280; };
struct SO2 { char pad[0x14]; int n14; char pad18[0x1E8 - 0x18]; struct SO2 *p1E8; };
struct SO {
    char pad[0xC]; struct VT *pvt; int pad10; int n14; char pad18[0x130 - 0x18]; int n130; char pad134[0x190 - 0x134];
    int n190; char pad194[0x1B0 - 0x194]; int n1B0; float f1B4; float f1B8; char pad1BC[0x2AC - 0x1BC];
    void *p2AC; char pad2B0[0x2BC - 0x2B0]; void *p2BC;
};
struct MSG { char pad[0x14]; struct SO2 *pso; char pad18[0x20 - 0x18]; int n20; int n24; int n28; char pad2C[0x50 - 0x2C]; int grf50; };
struct ACT { char pad[0x11C0]; };
extern struct ACT D_0036E740[];
int func_0013B500(void *object, int kind);
void func_001F4DD8(void *, void *, int, float);
void func_001F43D0(void *p, int a);
int func_001F43C8(void *self);
void func_001A9058(void *p, int n, float g);
void *func_001F4A80(void *object);
void func_00167D38(void *p, int k);
void func_00137588(void *anim, void *recv, int flags, void **out, float t, float rate);
void func_0026CD30(void *object, int enabled);
int func_0026C990(struct SO *p, struct MSG *pmsg) {
    if (p->pvt->e280.pfn((char *)p + p->pvt->e280.d, pmsg->n20)) return 0;
    if (!(pmsg->grf50 & 2)) return 0;
    if (func_0013B500(pmsg->pso, 0x59) && pmsg->pso->p1E8->n14 == p->n14) return 0;
    if (p->n190 != 1 && p->n190 != 4) return 0;
    func_001F4DD8(p, pmsg->pso, pmsg->n20, -3.40282346638528859812e+38f);
    if (pmsg->n28) {
        func_001F43D0(p, 0);
        p->n1B0 = 0;
    } else {
        func_001F43D0(p, func_001F43C8(p) - pmsg->n24);
    }
    func_001A9058(&D_0036E740[p->n130], 4, 0.75f);
    func_00167D38(func_001F4A80(p), 0);
    if (func_001F43C8(p) > 0) {
        p->f1B8 = p->f1B4;
        if (!p->p2BC) func_00137588(p->p2AC, p, 0, &p->p2BC, 0.0f, 1.0f);
    } else {
        func_0026CD30(p, 5);
    }
    return 1;
}
