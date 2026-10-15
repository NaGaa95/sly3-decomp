// Reference algorithm: src/hand/func_001C1BA0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct E;
struct O { char pad[0x190]; union { qword q; float g[4]; } a; union { qword q; float g[4]; } b; char p1[0x1DC - 0x1C0]; struct S *x1DC; };
struct S { char pad[0xE8]; int xF8; int xFC; int x100; struct E *x104; struct E *x108; struct O **x10C; int x110; int x114; };
struct M { struct O *po; void *pv; };
struct G { char pad[0x450C]; int x3D70; };
extern struct G D_00475480;
int func_001EDFE0(struct S *p, int z, qword a, qword b, int c, void **ap);
int func_001E7908(struct O *po, void *pv);
void func_001E7F58(int n, struct M *pm);
void func_001EE5C8(struct S *p);
void func_001EE2E8(int c, struct E *ae, int bit, float g0, float g1);
void func_001EE448(struct S *p, struct O *po)
{
    void *ap[0x20];
    int n, i;
    n = func_001EDFE0(p, 0, po->a.q, po->b.q, 0x20, ap);
    for (i = 0; i < n; i++) {
        if (func_001E7908(po, ap[i])) {
            struct M m;
            m.po = po;
            m.pv = ap[i];
            func_001E7F58(2, &m);
            return;
        }
    }
    if (p->xF8 >= p->xFC)
        func_001EE5C8(p);
    {
        int j;
        p->xF8++;
        for (j = 0; j < p->xF8; j++)
            if (!p->x10C[j]) break;
        p->x10C[j] = po;
        func_001EE2E8(p->x100, p->x104, j, po->a.g[0], po->b.g[0]);
        func_001EE2E8(p->x100, p->x108, j, po->a.g[1], po->b.g[1]);
    }
    po->x1DC = p;
    p->x100 += 2;
    p->x114 = ++D_00475480.x3D70;
}
