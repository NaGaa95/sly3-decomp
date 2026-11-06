// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct T { char pad[0x30]; VU v30; char pad2[0xA0 - 0x40]; int xA0; };
struct VTE { short d; short pad; void (*pf)(void *); };
struct S { int a[3]; struct VTE *vt; char pad[0x1B8 - 0x10]; int x1B8; int pad2; qword q1C0; };
struct T *func_0023DDA0(struct S *p, int a, int b);
qword func_0028E910(int a, int b, qword q);
VU *func_002BA818(VU *pv, qword q);
void func_00287000(struct S *p)
{
    struct T *t = func_0023DDA0(p, 0x27E, 0xD);
    if (t) {
        qword v = func_0028E910(p->x1B8, t->xA0, p->q1C0);
        func_002BA818(&t->v30, v);
        t->v30.f[3] = 1.0f;
        p->vt[20].pf((char *)p + p->vt[20].d);
    }
}
