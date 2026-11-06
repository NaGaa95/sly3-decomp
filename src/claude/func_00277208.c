// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pf)(void *, ...); };
struct M { char pad[0x18]; int x18; };
struct S { int a[3]; struct VTE *vt; char pad[0x13C - 0x10]; int x13C; char pad2[0x170 - 0x140]; qword q170; };
extern void *D_0036B250;
int func_001404D8(void *g, struct S *p, struct M *m, int *pv, qword q);
void func_00277208(struct S *p, struct M *m, int *pv)
{
    int k = p->x13C;
    if (k != 8) {
        if (k != 13)
            goto def;
        if (!D_0036B250)
            return;
        if (func_001404D8(D_0036B250, p, m, pv, p->q170)) {
            p->vt[9].pf((char *)p + p->vt[9].d);
            return;
        }
    }
    p->vt[80].pf((char *)p + p->vt[80].d, 3);
    return;
def: {
        struct M *a = m;
        int b;
        register int x18 __asm__("$3") = m->x18; /* pin: message kind in v1 */
        if (x18 == 1) {
            a = 0;
            b = 0;
        } else {
            b = *pv;
        }
        p->vt[10].pf((char *)p + p->vt[10].d, a, b, 0x13);
        p->vt[80].pf((char *)p + p->vt[80].d, 2);
    }
}
