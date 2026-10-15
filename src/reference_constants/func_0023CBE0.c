// Reference algorithm: src/hand/func_001F3C10.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct G { char pad[0x44FC]; int n; };
extern struct G D_00475480;
struct Q { char pad[0xC]; int n; };
struct A { char pad[0x10C]; struct Q *pq; };
void func_001C6418(struct G *pg, int n, struct Q *pq);
void func_0023CBE0(struct A *p)
{
    struct Q *pq = p->pq;
    if (pq && pq->n != D_00475480.n) {
        func_001C6418(&D_00475480, 0, pq);
        p->pq->n = D_00475480.n;
    }
}
