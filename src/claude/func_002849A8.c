// SLY3_CFLAGS: -Os -G0
struct E { int x0; float f4; char pad[0xC]; int x14; };
struct VTE { short d; short pad; void (*pf)(void *, int, int, int, void **, int); };
struct X { int a[3]; struct VTE *vt; char pad[0xB8 - 0x10]; int nB8; struct E *aBC; };
struct S { char pad[0x14]; struct X *x14; };
int func_002852B0(struct S *p, int a, int b);
int func_00283340(struct E *e, int a, int b);
void func_00284A90(struct S *p, int a, float g, int b);
void func_002849A8(struct S *p, int a, int b)
{
    if (func_002852B0(p, a, b)) {
        void *args[2];
        int i;
        args[0] = &a;
        args[1] = &b;
        p->x14->vt[3].pf((char *)p->x14 + p->x14->vt[3].d, 0x14, 0, 2, args, 0);
        for (i = 0; i < p->x14->nB8; i++) {
            struct E *e = &p->x14->aBC[i];
            if (func_00283340(e, a, b))
                func_00284A90(p, e->x0, e->f4, e->x14);
        }
    }
}
