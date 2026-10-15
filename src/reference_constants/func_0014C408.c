// Reference algorithm: src/hand/func_0013ADE8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct E { qword a; qword b; float g; int id; int pad[2]; };
struct P { char pad[0xD4]; int xE4; char pad2[0x1DC - 0xD8]; int c; int n; struct E *ae; };
struct Q { char pad[0x60]; int id; };
struct O { char pad[0xDC]; struct Q *pq; };
struct S { int x0; struct O *po; };
struct G { int x; };
extern struct G D_00475480;
void func_0023EDD0(struct P *p, struct S *ps, int a2, int a3, int a4, int a5);
void func_001CB8B0(struct G *pg, int n, struct S *ps, qword a, qword b, int k, int x, int y, float g, int z);
void func_0014C408(struct P *p, struct S *ps, int a2, int a3, int a4, int a5)
{
    func_0023EDD0(p, ps, a2, a3, a4, a5);
    if (p->c) {
        struct E *pe;
        for (pe = p->ae; pe < p->ae + p->n; pe++) {
            if (pe->id == ps->po->pq->id) {
                func_001CB8B0(&D_00475480, p->xE4, ps, pe->a, pe->b, 9, 0, 0, pe->g, a5);
                return;
            }
        }
    }
}
