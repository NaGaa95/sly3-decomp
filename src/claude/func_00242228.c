// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Undo of func_00241FC0/func_00242048: restore saved node states and free the owner record.
struct VTE { short d; short pad; void (*pfn)(void *); };
struct VTE2 { short d; short pad; void (*pfn)(void *, int); };
struct VT { char pad[8]; struct VTE e8; struct VTE e10; char pad18[0xB8 - 0x18]; struct VTE2 eB8; };
struct LO { char pad[0xC]; struct VT *pvt; char pad10[0x68 - 0x10]; float f68; char pad6C[0x128 - 0x6C]; unsigned long flags; };
struct NODE { int kind; struct LO *plo; float g; struct NODE *next; };
struct ListHead { void *first; void *last; int nextOffset; };
struct Owner { struct LO *owner; struct ListHead children; struct Owner *next; };
extern unsigned char D_0047A434[];
extern unsigned char D_0047A458[];
void func_00138B68(void *p, float g);
void func_0011B028(void *list, void *node);
void Free__9POOLSTATEPv(void *pool, void *p);
void func_00242228(struct LO *p)
{
    struct Owner *e;
    struct NODE *n, *next;
    if (!(p->flags & 0x40)) return;
    p->flags &= ~0x40;
    for (e = *(struct Owner **)(D_0047A434 + 0x18); e; e = e->next)
        if (e->owner == p) break;
    if (!e) return;
    for (n = e->children.first; n; n = next) {
        next = n->next;
        switch (n->kind) {
        case 0x2F:
            n->plo->pvt->eB8.pfn((char *)n->plo + n->plo->pvt->eB8.d, 1);
            break;
        case 0xAB:
            func_00138B68(n->plo, 1.0f);
            n->plo->pvt->e10.pfn((char *)n->plo + n->plo->pvt->e10.d);
            break;
        case 0xC3:
            n->plo->f68 = n->g;
            n->plo->pvt->e10.pfn((char *)n->plo + n->plo->pvt->e10.d);
            break;
        }
        Free__9POOLSTATEPv(D_0047A458, n);
    }
    func_0011B028(D_0047A434 + 0x18, e);
    Free__9POOLSTATEPv(D_0047A434, e);
}
