// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VTE { short d; short pad; void (*pf)(void *, ...); };
struct O { int a[3]; struct VTE *vt; };
struct SP { void *p; };
struct V { char pad[0x11C0]; };
struct S { char pad[0x130]; int x130; char pad134[0x198 - 0x134]; int x198; char pad19c[0x1A0 - 0x19C]; int k; float t;
           char pad1a8[0x2AC - 0x1A8]; struct O *x2AC; void *x2B0; struct SP r2B4; char pad2b8[0x2C8 - 0x2B8]; struct O *x2C8; int pad2cc; int x2D0; };
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
extern struct V D_0036E740[];
void func_00244CA8(void *p, float g);
void func_002BBCD8(struct SP *ps, void *p);
void *func_002459F8(void *p);
void func_00244F08(void *p, int k);
void func_00262280(struct O *o, int k);
void func_00262450(struct O *o, int k);
void func_00287740(struct S *p);
void func_00286630(struct S *p, int k);
void func_001C8FB0(struct O *o, struct S *p);
void func_0014CE20(struct O *o);
void func_001A9058(struct V *pv, int k, float g);
void *func_001A91D8(struct V *pv);
void func_00167D38(void *p, int k);
static inline void Release(struct SP *ps, float g)
{
    if (ps && ps->p) {
        func_00244CA8(ps->p, g);
        func_002BBCD8(ps, 0);
    }
}
void func_00286B00(struct S *p, int k)
{
    if (p->k == k)
        return;
    switch (p->k) {
    case 2:
        Release(&p->r2B4, 0.1f);
        if (p->x2C8)
            func_00262280(p->x2C8, 0x3E2);
        break;
    case 3:
        p->k = k;
        p->t = g_clock.t;
        p->x2AC->vt[9].pf((char *)p->x2AC + p->x2AC->vt[9].d);
        func_00287740(p);
        break;
    }
    p->k = k;
    p->t = g_clock.t;
    switch (k) {
    case -1:
        Release(&p->r2B4, 0.0f);
        if (p->x2C8)
            func_00262280(p->x2C8, 0x3E2);
        break;
    case 2: {
        void *o = func_002459F8(p->x2B0);
        func_00244F08(o, 0);
        func_002BBCD8(&p->r2B4, o);
        if (p->x2C8)
            func_00262450(p->x2C8, 0x3E2);
        break;
    }
    case 3:
        if (p->x198)
            func_00286630(p, 1);
        func_001C8FB0(p->x2AC, p);
        p->x2AC->vt[8].pf((char *)p->x2AC + p->x2AC->vt[8].d);
        func_0014CE20(p->x2AC);
        if (p->x130 != -1) {
            void *r;
            func_001A9058(&D_0036E740[p->x130], 4, 0.75f);
            r = func_001A91D8(&D_0036E740[p->x130]);
            if (r)
                func_00167D38(r, 0);
        }
        if (p->x2C8) {
            p->x2C8->vt[54].pf((char *)p->x2C8 + p->x2C8->vt[54].d);
            p->x2D0 = -1;
        }
        break;
    }
}
