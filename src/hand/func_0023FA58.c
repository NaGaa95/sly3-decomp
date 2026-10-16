// SLY3_CFLAGS: -Os -G0
typedef unsigned long ulong;
struct VTE { short d; short p; void (*pfn)(void *, void *); };
struct VT { struct VTE a[46]; };
struct A { char pad[0xC]; struct VT *pvt; };
struct L { char pad[0x24]; struct L *next; ulong fl; char pad2[0x54 - 0x30]; struct L *first; char pad3[0x60 - 0x58]; struct L *end; };
void func_001507E0(struct L *, struct A *);
void func_0023FA58(struct A *pa, struct L *p)
{
    struct L *q;
    pa->pvt->a[45].pfn((char *)pa + pa->pvt->a[45].d, p);
    for (q = p->first; q != p->end; q = q->next)
        if (!(q->fl & (1L << 53))) func_001507E0(q, pa);
}
