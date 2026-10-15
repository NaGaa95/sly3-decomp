// Sly 2 reference: src/hand/func_001FFCF8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct KV { int k; int v; };
struct T { int c; struct KV *a; };
extern struct T D_002ED518[];
struct R { int n0; int n4; };
struct VTE { short d; short p; struct R *(*pfn)(void *); };
struct VT { struct VTE a[7]; };
struct X { char pad[0xC]; struct VT *pvt; };
int func_00249CF8(struct X *px, int k)
{
    struct R *r = px->pvt->a[6].pfn((char *)px + px->pvt->a[6].d);
    struct T *t = &D_002ED518[r->n4];
    int lo = 0, hi = t->c - 1;
    struct KV *a = t->a;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (a[mid].k == k) return a[mid].v;
        if (k < a[mid].k) hi = mid - 1;
        else lo = mid + 1;
    }
    return 0;
}
