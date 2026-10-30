// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Port of Sly 2 src/hand/func_0013B5E8.c (Sly 3 offsets/addresses). */
typedef int qword __attribute__((mode(TI)));
struct AREQ { int cb; int cbAlign; };
struct X { char pad[0x60]; int x60; };
struct O { char pad[0xDC]; struct X *px; };
struct S { int x0; struct O *po; int x8; int xC; int x10; char pad[0x84 - 0x14]; int x84; };
struct P { char pad[0xDC]; struct X *px; char pad1[0x13C - 0xE0]; float g13C; float g140; char pad2[0x160 - 0x144]; qword q160; };
struct HIT { int a[12]; };
extern char D_00475480[];
void func_0025CE90();
void func_0025D0D8(void *pg, qword q, void (*pfn)(), struct X *px, float g, int *pc, struct S ***paps);
void *PvAllocSlot(struct AREQ *preq) __asm__("PvAllocSlot__FP8ALLOCREQ");
int func_0013B500(int n, int k);
int func_001CD098(qword q, struct S *ps, int n, int a, int b, int c, float g, struct HIT *phit);
void func_0014CD78(struct P *p, int *pn, struct O **apo);
void func_0014CBB8(struct P *p, int *pc, struct O ***papo)
{
    struct AREQ req;
    int c;
    struct S **aps;
    int n;
    struct O **apo;
    int i;
    { float a = p->g13C; float b = p->g140; func_0025D0D8(D_00475480, p->q160, func_0025CE90, p->px, b >= a ? b : a, &c, &aps); }
    if (c == 0) {
        *pc = 0;
        *papo = 0;
        return;
    }
    req.cb = c * 4;
    req.cbAlign = 0x10;
    apo = (struct O **)PvAllocSlot(&req);
    n = 0;
    for (i = 0; i < c; i++) {
        struct S *ps = aps[i];
        struct HIT hit;
        int x60 = ps->po->px->x60;
        if (ps->x10 == 1)
            continue;
        if (x60 == p->px->x60)
            continue;
        if (ps->x84 && !func_001CD098(p->q160, ps, 0x7FFFFFFF, 0, 0, 1, func_0013B500(x60, 0x33) ? p->g140 : p->g13C, &hit))
            continue;
        apo[n] = ps->po;
        n++;
    }
    func_0014CD78(p, &n, apo);
    *pc = n;
    *papo = apo;
}
