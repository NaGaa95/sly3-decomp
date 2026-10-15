// Reference algorithm: src/hand/func_00149B58.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct K { short x; short y; union { short s; int i; } u; } K;
typedef struct N { int a; K k; int d; struct N *pnNext; } N;
struct P { char pad[0x442C]; char pool[0x18]; N *pnHead; N *pnTail; };
void func_0011E1F0(void *pool, N *pn);
static __inline__ int FMatchK(K *pa, K *pb)
{
    if (pa->y != pb->y) return 0;
    if (pa->y != -1 && pa->u.s == pb->u.s) return 1;
    return pa->u.i == pb->u.i;
}
void func_0015DD68(struct P *p, unsigned int grf, int a, K k, int d)
{
    N **ppn = &p->pnHead;
    N *pn;
    while ((pn = *ppn) != 0) {
        if ((grf & 1) && a != pn->a) goto next;
        if (grf & 2) {
            if (k.y != pn->k.y) goto next;
            if (k.y == -1 || k.u.s != pn->k.u.s) {
                if (k.u.i != pn->k.u.i) goto next;
            }
        }
        if ((grf & 4) && d != pn->d) goto next;
        *ppn = pn->pnNext;
        func_0011E1F0(p->pool, pn);
        continue;
    next:
        ppn = &pn->pnNext;
    }
    if (!p->pnHead) p->pnTail = 0;
}
