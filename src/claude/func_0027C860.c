// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct XF { char pad[0x30]; qword pos; };
struct VTE { short d; short pad; struct XF *(*pf)(void *); };
struct SP { void *p; };
struct S { int a[3]; struct VTE *vt; char pad[0x3B0 - 0x10]; int k; float t; void *x3B8; char a3BC[0x3D0 - 0x3BC];
           void *x3D0, *x3D4; char pad3d8[0x3EC - 0x3D8]; struct SP r3EC, r3F0; };
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
void func_00244CA8(void *p, float g);
void func_002BBCD8(struct SP *ps, void *p);
void *func_002459F8(void *p);
void func_00244F08(void *p, int k);
void func_00244E08(void *p, float g);
void func_0022EA88(void *p, qword q, void *a, qword *pq, qword *b, float *c, void *pv);
static inline struct XF *Xf(struct S *o) { return o->vt[36].pf((char *)o + o->vt[36].d); }
static inline int FOff(int k) { return k == -1 || k == 0; }
static inline void Release(struct SP *ps)
{
    if (ps && ps->p) {
        func_00244CA8(ps->p, 0.0f);
        func_002BBCD8(ps, 0);
    }
}
static inline void Attach(struct SP *ps, void *pv)
{
    void *p = func_002459F8(pv);
    func_00244F08(p, 0);
    func_002BBCD8(ps, p);
}
void func_0027C860(struct S *p, int k)
{
    if (k == p->k)
        return;
    if (FOff(p->k) != FOff(k)) {
        if (FOff(k)) {
            Release(&p->r3EC);
            Release(&p->r3F0);
        } else {
            float g;
            void *o;
            g = 0.0f;
            o = func_002459F8(p->x3D0);
            func_00244F08(o, 0);
            func_002BBCD8(&p->r3EC, o);
            o = func_002459F8(p->x3D4);
            func_00244F08(o, 0);
            func_002BBCD8(&p->r3F0, o);
            func_00244E08(p->r3EC.p, g);
            func_00244E08(p->r3F0.p, g);
        }
    }
    p->k = k;
    p->t = g_clock.t;
    if (k < 4)
        if (k >= 2)
        func_0022EA88(p->x3B8, Xf(p)->pos, 0, 0, 0, 0, p->a3BC);
}
