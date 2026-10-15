// Invoke the original virtual update slot and visit child-list entries whose Sly 3 exclusion bit 53 is clear.
// Reference algorithm: src/hand/func_001F66F0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned long ulong;
struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { struct VTE a[46]; };
struct A { char pad[0xC]; struct VT *pvt; };
struct L { char pad[0x24]; struct L *next; ulong fl; char pad2[0x54 - 0x30]; struct L *first; char pad3[0x60 - 0x58]; struct L *end; };
void func_001507E0(struct L *, struct A *);
void func_0023FA58(struct A *pa, struct L *p)
{
    struct L *q;
    pa->pvt->a[45].pfn((char *)pa + pa->pvt->a[45].d);
    for (q = p->first; q != p->end; q = q->next)
        if (!(q->fl & (1L << 53))) func_001507E0(q, pa);
}
