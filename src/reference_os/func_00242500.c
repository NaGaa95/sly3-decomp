// Sly 2 reference: src/hand/func_001F8910.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct E { int k; int pad[2]; int nC; struct E *next; };
struct Q { char pad[0x90]; struct E *pe; };
struct P { char pad[0x20]; void *p20; struct Q *pq; };
void func_0028EDC8(void *, struct Q *, struct E *);
void func_001306C8(struct E *);
void func_0028EE98(void *, struct Q *);
void func_0028F068(void *, struct Q *, int);
void func_0028F260(void *, struct Q *);
struct E *func_00242500(struct P *p, int k, int n, int m)
{
    struct E *pe;
    for (pe = p->pq->pe; pe; pe = pe->next) {
        if (pe->k != k) continue;
        if (n == -1) {
            func_0028EDC8(p->p20, p->pq, pe);
            func_001306C8(pe);
            return 0;
        }
        if (m != pe->nC) {
            pe->nC = m;
            func_0028EE98(p->p20, p->pq);
        }
        if (pe == p->pq->pe) {
            func_0028F068(p->p20, p->pq, n);
            func_0028F260(p->p20, p->pq);
        }
        return pe;
    }
    return 0;
}
