// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Port of Sly 2 src/hand/func_001467A0.c (Sly 3 offsets/addresses; positions through the vtable matrix). Owns jtbl 0x320740. */
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; struct M4 *(*pfn)(void *); };
struct VT { char pad[0x120]; struct VTE e120; };
struct PO { char pad[0xC]; struct VT *pvt; char pad0[0x33C - 0x10]; int x2DC; float g2E0; char pad2[0xE44 - 0x344]; int xDF4; char pad3[0x10D4 - 0xE48]; int x18D8; };
struct T { char pad[0xC]; struct VT *pvt; char pad0[0x360 - 0x10]; int x330; };
struct P { char pad[0x10]; struct PO *p10; char pad2[0x30 - 0x14]; int x30; float x34; struct T *p38; };
extern struct CLOCK { float t; } g_clock;
extern qword D_00317530;
/* rodata 0x320730/0x320734 (named float constants of this unit, read by address) */
extern const float D_00320730;
extern const float D_00320734;
void func_002389A0(struct P *p);
int func_001C8610(struct T *p);
void func_001599E0(struct P *p, int n);
float func_0011E940(float gMin, float gMax);

static __inline__ struct M4 *Mat(void *p) { struct PO *po = (struct PO *)p; return po->pvt->e120.pfn((char *)po + po->pvt->e120.d); }
static __inline__ float Dot(qword a, qword b)
{
    qword r, t;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(r), "=j"(t) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r));
    return g;
}

static __inline__ float SafeNormalize(qword *pv, qword *pvDefault)
{
    register qword v __asm__("vf3") = *pv; /* register pin: the target keeps the vector in vf3, length in vf2 */
    qword t, l;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(t), "=j"(l) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(t), "0"(l));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
    if (g < 0.0001f)
        *pv = *pvDefault;
    else {
        qword r;
        __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=&j"(r) : "j"(l), "j"(v));
        *pv = r;
    }
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
    return g;
}

void func_00159358(struct P *p)
{
    union { qword q; float f[4]; } d;
    float g;
    int state;
    func_002389A0(p);
    if (p->x30 == -1)
        return;
    if (p->p10->xDF4 != -1 || !func_001C8610(p->p38) || p->p38->x330) {
        func_001599E0(p, -1);
        return;
    }
    {
        qword a = Mat(p->p38)->r[3];
        qword b = Mat(p->p10)->r[3];
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d.q) : "j"(a), "j"(b));
        d.f[2] = 0.0f;
        g = SafeNormalize(&d.q, &D_00317530);
    }
    do {
        state = p->x30;
        switch (state) {
        case 0:
            if (g < 450.0f) {
                struct M4 *pm = Mat(p->p10);
                if (0.8f < Dot(pm->r[0], d.q)) {
                    if (func_0011E940(0.0f, 1.0f) < 0.3f)
                        func_001599E0(p, 3);
                    else
                        func_001599E0(p, 2);
                }
            } else if (D_00320734 < g) {
                func_001599E0(p, 1);
            }
            break;
        case 1:
            if (g < D_00320730)
                func_001599E0(p, 0);
            break;
        case 2:
            if (p->p10->x18D8 == -1 && 0.1f < g_clock.t - p->x34)
                func_001599E0(p, -1);
            break;
        case 3: {
            float t = g_clock.t;
            if (0.1f < t - p->x34) {
                struct PO *po = p->p10;
                if (po->x2DC != -1) {
                    if (po->x2DC == 1 && 0.2f < t - po->g2E0)
                        func_001599E0(p, 4);
                } else
                    func_001599E0(p, -1);
            }
            break;
        }
        case 4:
            if (p->p10->x18D8 == -1 && 0.1f < g_clock.t - p->x34)
                func_001599E0(p, -1);
            break;
        }
    } while (p->x30 != state);
}

/* Next .rodata item of the original unit (an LM {0.1, 1.0} read by func_00159708); it follows the jump table. */
const float D_00320758[2] = { 0.1f, 1.0f };
