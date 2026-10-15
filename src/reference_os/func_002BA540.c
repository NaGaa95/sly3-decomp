// Sly 2 reference: src/hand/func_002569F8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef struct VT { short d; short pad; void *pfn; } VT;
typedef struct A { VT *vt; } A;
typedef struct E { unsigned int key; int k; int v; struct E *next; } E;
typedef struct H { unsigned int c; E **ap; int count; A *pa; } H;
void *func_00292034(void *, int, int);
void func_002BA408(H *, int);
unsigned int func_0011BF50(unsigned char *);

int *func_002BA540(H *h, int *pk, int *pv)
{
    unsigned int hash, i;
    E *e;
    h->count++;
    if (h->c == 0)
        func_002BA408(h, 0x35);
    hash = func_0011BF50((unsigned char *)*pk);
    i = hash % h->c;
    e = ((E *(*)(void *, int, int))h->pa->vt[1].pfn)((char *)h->pa + h->pa->vt[1].d, 0x10, 3);
    func_00292034(e, 0, 0x10);
    e->key = hash;
    e->k = *pk;
    e->v = *pv;
    e->next = h->ap[i];
    h->ap[i] = e;
    return &e->v;
}
