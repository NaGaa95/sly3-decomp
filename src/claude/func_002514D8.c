// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_002514D8: state change (cf. Sly 2 func_00207030), rewritten for the Sly 3 layout.
typedef int qword __attribute__((mode(TI)));
struct V3 { float x, y, z; };
struct Y14 { char pad[0x68]; float f68; };
struct Y { char pad[0x14]; struct Y14 *p14; };
struct X { char pad[0x40]; void *p40; };
struct Z { char pad[0x30]; int k30; int n34; float f38; };
struct VTE { short delta; short pad; void (*pfn)(void *); };
struct VO { char pad[0xC]; struct VTE *vt; char pad10[4]; void *p14; char pad18[0x48]; void *p60; };
struct S
{
    char pad[0x1A0];
    struct V3 v1A0;
    char pad1AC[0x29C - 0x1AC];
    char sub29C[0x112C - 0x29C];
    int k;
    float t;
    char pad1134[0x11D8 - 0x1134];
    void *p11D8;
    char pad11DC[4];
    float f11E0;
    char pad11E4[0x17C8 - 0x11E4];
    struct VO *p17C8;
};
struct W { char pad[0x19C0]; void *p19C0; };
extern struct { float t; float dt; } g_clock;
extern struct W *D_0036B250;
extern char D_00475480[];
static const float RO_003272E0[4] __attribute__((aligned(16))) = { 0.5f, 0.5f, 0.5f, 0.0f };
int func_002513D0(struct S *p, int k);
void func_0012F4F8(void *p, qword q);
void func_00203030(struct VO *p);
void *func_002387A8(void *p, int n);
void *func_001FE728(void *p, int n);
struct Y *func_00254F80(void *p);
void func_00138B88(struct Y *y, float f);
int func_001F4AD0(void *p, int n);
void func_0019AD90(struct Z *z);
void *func_002459F8(int n);
void func_00244F08(void *p, struct S *ps);

static inline qword Splat(float f)
{
    qword t, q;
    __asm__("mfc1 %0,%2\n\tpextlw %0,%0,%0\n\tpextlw %1,%0,%0" : "=&r"(t), "=r"(q) : "f"(f));
    return q;
}

void func_002514D8(struct S *p, int k)
{
    int old;
    if (k == p->k)
        return;
    if (!func_002513D0(p, k))
        return;
    old = p->k;
    p->k = k;
    p->t = g_clock.t;
    switch (old) {
    case 0xE:
    case 0x10:
        if (p->p11D8)
            func_0012F4F8(p->p11D8, Splat(p->f11E0));
        break;
    case 0xC:
    case 0xF:
        if (p->p17C8) {
            func_00203030(p->p17C8);
            {
                struct VO *v = p->p17C8;
                struct VTE *e = &v->vt[2];
                e->pfn((char *)v + e->delta);
            }
            p->p17C8 = 0;
        }
        break;
    case 0x16: {
        struct X *x = func_002387A8(p->sub29C, 0xC9);
        if (x && x->p40) {
            struct Y *y = func_00254F80(x->p40);
            if (y)
                func_00138B88(y, y->p14->f68);
        }
        break;
    }
    case 0x14: {
        struct Z *z = func_002387A8(p->sub29C, 0xC8);
        if (z && z->k30 == 0x10 && z->n34 == func_001F4AD0(D_00475480, 0) && z->f38 == 3.40282346639e+38f)
            func_0019AD90(z);
        break;
    }
    }
    switch (k) {
    case 0xE:
    case 0x10:
        if (p->p11D8)
            func_0012F4F8(p->p11D8, *(qword *)RO_003272E0);
        func_00244F08(func_002459F8(0), p);
        break;
    case 0xC:
    case 0xF:
        if (D_0036B250 && D_0036B250->p19C0) {
            struct VO *v = func_001FE728(D_0036B250->p19C0, 1);
            p->p17C8 = v;
            if (v) {
                struct VTE *e = &v->vt[1];
                e->pfn((char *)v + e->delta);
                p->p17C8->p14 = p;
                p->p17C8->p60 = p;
            }
        }
        break;
    case 0x16: {
        struct X *x = func_002387A8(p->sub29C, 0xC9);
        if (x && x->p40) {
            struct Y *y = func_00254F80(x->p40);
            if (y)
                func_00138B88(y, 0.0f);
        }
        {
            struct V3 *pv = &p->v1A0;
            pv->z = 0;
            pv->y = 0;
            pv->x = 0;
        }
        break;
    }
    case 0x14: {
        struct Z *z = func_002387A8(p->sub29C, 0xC8);
        if (z) {
            switch (z->k30) {
            case 1: case 2: case 3: case 4:
            case 0xC: case 0xE: case 0xF: case 0x10:
                func_0019AD90(z);
                break;
            }
        }
        break;
    }
    }
}
