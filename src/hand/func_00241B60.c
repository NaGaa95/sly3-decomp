// Lazily allocate and initialize a resource with the type-specific scalar defaults, returning its cached pointer.
// Reference algorithm: src/hand/func_001F8300.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Q { void *p0; int pad; float g8; float gC; };
struct E { char pad[0xDC]; struct Q *pq; };
struct P { char pad[0xD8]; struct E *pe; };
struct CB { int cb; int n; };
void *func_001D2538(struct CB *);
int func_0013B500(void *, int);
static inline void *PvAllocMsg(struct CB *pcb, int cb, int n) { pcb->cb = cb; pcb->n = n; return func_001D2538(pcb); }
struct Q *func_00241B60(struct P *p)
{
    if (!p->pe) return 0;
    if (!p->pe->pq) {
        struct CB cb;
        struct Q *q = PvAllocMsg(&cb, 0x70, 0x10);
        q->p0 = p;
        if (func_0013B500(p, 0x33)) q->g8 = 150.0f;
        else q->g8 = 75.0f;
        q->gC = 1.0f;
        p->pe->pq = q;
    }
    return p->pe->pq;
}
