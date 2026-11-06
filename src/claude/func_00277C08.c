// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from Sly 2 func_00224BF8 (probe a ring pattern and the nearby objects).
typedef int qword __attribute__((mode(TI)));
typedef struct MARK { int a[4]; } MARK;
struct VTE { short d; short pad; void (*pf)(void *); };
struct X { int a[3]; struct VTE *vt; };
struct B { char pad[0x70]; qword pos; };
struct A { struct B *pb; };
struct S { char pad[0xDC]; void *xDC; };
struct G { char pad[0x47B4]; void *x47B4; };
struct R { char pad[0x54]; int x54; };
extern struct G D_00475480;
extern const int D_00329210[11];
extern const float D_003291E0[11];
void func_0025CE90();
MARK *func_001D2770(MARK *pm);
void func_001D2798(MARK *pm, int n);
void func_0025D0D8(struct G *pg, qword pos, void (*pfn)(), void *pv, float r, int *pc, struct A ***papa);
qword func_0011FDD8(float a, float b, float c);
qword func_001205F0(qword v, float r);
void func_00277830(struct S *p, int a, int b, int d, qword pos, qword posT, int c, struct A **apa, int cMax, int *pcx, struct X **ax);
void func_00240A28(struct X *px);
struct R *func_001738C0(void *pv, qword pos, struct S *p);
static __inline__ qword VAdd(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static __inline__ qword VSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
void func_00277C08(struct S *p, int a, int b, int d, qword pos, float r)
{
    MARK mark;
    struct X *ax[0x20];
    int c;
    struct A **apa;
    int cx;
    int i, j, k, m;
    func_001D2770(&mark);
    func_0025D0D8(&D_00475480, pos, func_0025CE90, p->xDC, r, &c, &apa);
    cx = 0;
    for (i = 0; i < sizeof(D_00329210) / sizeof(D_00329210[0]); i++) {
        for (j = 0; j < D_00329210[i]; j++) {
            qword v = func_0011FDD8((float)j * 2.0f * 3.1415927f / (float)D_00329210[i], D_003291E0[i], r);
            func_00277830(p, a, b, d, pos, VAdd(pos, v), c, apa, 0x20, &cx, ax);
        }
    }
    for (k = 0; k < c; k++) {
        qword v = func_001205F0(VSub(apa[k]->pb->pos, pos), r);
        func_00277830(p, a, b, d, pos, VAdd(pos, v), c, apa, 0x20, &cx, ax);
    }
    for (m = 0; m < cx; m++) {
        func_00240A28(ax[m]);
        ax[m]->vt[2].pf((char *)ax[m] + ax[m]->vt[2].d);
        ax[m] = 0;
    }
    func_001738C0(D_00475480.x47B4, pos, p)->x54 = 1;
    func_001D2798(&mark, 2);
}
