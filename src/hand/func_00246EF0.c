// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct T { char pad[0x44]; struct T *pnext; };
struct S { char pad[0xF0]; struct T *pt; struct T *pt2; };
int func_00246EF0(struct S *p, struct T *x) { struct T *pt; for (pt = p->pt; pt; pt = pt->pnext) if (pt == x) return 1; return p->pt2 != x ? 2 : 0; }
