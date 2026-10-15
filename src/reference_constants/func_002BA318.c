// Reference algorithm: src/hand/func_002567D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct VT { short d; short pad; void *pfn; } VT;
typedef struct A { VT *vt; } A;
typedef struct E { int key; int k; int v; struct E *next; } E;
typedef struct H { int c; E **ap; int count; A *pa; } H;
void *func_00292034(void *, int, int);

#define FREE(pa, p) ((void (*)(void *, void *))(pa)->vt[4].pfn)((char *)(pa) + (pa)->vt[4].d, p)

void func_002BA318(H *h)
{
    int i;
    for (i = 0; i < h->c; i++) {
        E *e = h->ap[i];
        while (e) {
            E *next = e->next;
            FREE(h->pa, e);
            e = next;
        }
    }
    func_00292034(h->ap, 0, h->c * 4);
    h->count = 0;
    FREE(h->pa, h->ap);
    h->c = 0;
    h->ap = 0;
}
