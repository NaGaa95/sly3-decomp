// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pf)(void *, ...); };
struct XF { char pad[0x80]; qword q80; };
typedef union { qword q; float f[4]; } VU;
struct O { int a[3]; struct VTE *vt; char pad10[0xD8 - 0x10]; struct XF *xD8; char padDC[0x320 - 0xDC]; char a320[0x35C - 0x320];
           int x35C; char pad360[0x370 - 0x360]; VU v370; char pad380[0x1520 - 0x380]; int x1520; char pad1524[0x19E0 - 0x1524]; int x19E0; };
struct S { void *x0; char pad4[0x10 - 4]; struct O *po; char pad14[0x30 - 0x14]; qword q30; char pad40[0xF0 - 0x40]; qword qF0; qword q100;
           char pad110[0x144 - 0x110]; float g144; void *x148; };
extern struct O *D_0036B250;
extern struct O *D_00370AC0;
void func_0013FB20(struct O *o, int k);
qword func_00250600(struct O *o);
qword func_00212480(qword a, qword b, qword c, float g);
void func_001B7268(void *p, int k, int a, int b, float g);
void func_001C7A00(struct O *o, int a, int b);
void func_0023EBF8(struct O *o, int k);
void func_0023EC98(struct O *o, int k);
qword func_001C94E8(void *p, int k, qword q);
int func_0013B500(void *pj, int k);
void func_002412C8(void *p, float g);
void func_002730D8(struct S *p)
{
    struct O *o = p->po;
    if (o == D_0036B250) {
        if (o->x1520 != 10)
            goto done;
        func_0013FB20(o, 1);
    } else if (o == D_00370AC0) {
        struct O *g;
        if (o->x19E0 != 20)
            goto done;
        p->q100 = func_00212480(func_00250600(o), p->qF0, D_00370AC0->xD8->q80, p->g144);
        func_001B7268(D_00370AC0->a320, 8, 0, 0, 1.0f);
        g = D_00370AC0;
        g->v370.q = p->q100;
        g->x35C = 3;
        g->v370.f[2] = 0.0f;
    } else {
        func_001C7A00(o, 0, 3);
        func_0023EBF8(p->po, 0);
        func_0023EC98(p->po, 0);
    }
    p->po->vt[40].pf((char *)p->po + p->po->vt[40].d, p->q100);
    {
        struct O *t = p->po;
        struct VTE *e = &t->vt[41];
        e->pf((char *)t + e->d, func_001C94E8(p->x0, 0, p->q30));
    }
    if (func_0013B500(p->po, 0x71))
        p->po->vt[80].pf((char *)p->po + p->po->vt[80].d, 1);
done:
    if (p->x148)
        func_002412C8(p->x148, 0.25f);
}
