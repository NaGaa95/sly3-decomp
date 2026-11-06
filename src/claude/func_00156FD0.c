// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00156FD0 (agent A43, from A18 wip): the 0 <= f108 test guards BOTH func_001F4DD8 and func_001854C8
// (target bc1f skips to the 0.5f setup); that block boundary also fixes the fAny=1 delay slot and the beqz fill.
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; struct VTE e120; };
struct E { int pad[2]; void *x8; char pad2[0x40 - 0xC]; };
struct SO { struct E ae[2]; char pad[0xAC - 0x80]; struct SO *pnext; };
struct LN { struct SO *pso; struct LN *pnext; };
struct X { char pad[0x64]; struct LN *x64; };
struct K { char pad[0x48]; unsigned char *x48; };
struct PO {
    char pad[0xC]; struct VT *pvt; char pad1[0xDC - 0x10]; struct X *xDC; char pad2[0x130 - 0xE0]; int x130;
    char pad3[0x33C - 0x134]; int x33C; char pad4[0x115C - 0x340]; struct K *x115C;
};
struct T { char pad[0x108]; float x108; };
struct R { char pad[0x3C]; int x3C; char pad2[0x48 - 0x40]; int x48; };
struct P { struct PO *p0; float g4; int pad[2]; qword pos; float d20; float t24; int f28; int f2C; };
extern struct CLOCK { float t; } g_clock;
extern char D_00475480[];
extern char D_0036C700[];
int func_00156700(struct PO *);
int func_001A9478(void *, int);
int func_0013B500(struct T *, int);
struct R *func_002387A8(void *, int);
void func_001F4DD8(struct T *, struct PO *, int, float);
void func_001854C8(void *, int, void *);
void func_002412C8(struct T *, float);
int func_00198D78(float, float, qword *, int, int);
int func_001DA038(qword *);
void func_001C04E8(struct PO *, qword);

static __inline__ struct M4 *Matrix(struct PO *p)
{
    struct VTE *e = &p->pvt->e120;
    return ((struct M4 *(*)(void *))e->pfn)((char *)p + e->d);
}
static __inline__ float GDistXY(qword a, qword b)
{
    qword d;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0, %0, %0\n\tvaddy.x %0, %0, %0y" : "+j"(d));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}

static __inline__ int IOther(struct PO *p0, struct SO *pso) { return p0 == pso->ae[0].x8 ? 0 : 1; }

void func_00156FD0(struct P *p)
{
    if (p->f28) {
        if (p->p0->x33C == -1)
            p->f28 = 0;
        return;
    }
    if (!func_00156700(p->p0))
        return;
    if (g_clock.t < p->t24)
        return;
    p->t24 = g_clock.t + p->g4;
    if (func_001A9478(D_00475480, p->p0->x130)) {
        int fAny = 0;
        struct LN *pln;
        for (pln = p->p0->xDC->x64; pln; pln = pln->pnext) {
            struct SO *pso;
            for (pso = pln->pso; pso; pso = pso->pnext) {
                int i = p->p0 == pso->ae[0].x8;
                struct T *po = ((struct E *)((int)pso + (i << 6)))->x8;
                if (func_0013B500(po, 0x3A)) {
                    struct R *pr = func_002387A8((char *)po + 0x29C, 0xD3);
                    if (!pr || !pr->x48) {
                        if (0.0f <= po->x108) {
                            func_001F4DD8(po, p->p0, -1, -3.40282347e+38f);
                            func_001854C8(D_0036C700, 0x10, po);
                        }
                        func_002412C8(po, 0.5f);
                        fAny = 1;
                    }
                }
            }
        }
        if (fAny)
            return;
    }
    if (p->p0->x115C) {
        if (*p->p0->x115C->x48 != 0x30)
            return;
    } else {
        struct R *pr = func_002387A8((char *)p->p0 + 0x29C, 0xEF);
        if (!pr)
            return;
        if (pr->x3C)
            return;
    }
    {
        float g = GDistXY(Matrix(p->p0)->r[3], p->pos);
        if (p->d20 - g < p->g4 * 30.0f) {
            p->f2C = 0;
            func_001854C8(D_0036C700, 0x5A, p->p0);
            if (!p->f2C) {
                qword v = p->pos;
                if (func_00198D78(100.0f, -350.0f, &v, 0, 0) || func_001DA038(&v)) {
                    func_001C04E8(p->p0, v);
                    p->f28 = 1;
                }
            }
        }
        p->d20 = g;
    }
}