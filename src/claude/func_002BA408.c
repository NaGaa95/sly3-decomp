// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Reference: Sly 2 src/hand/func_002568C0.c; target Sly 3 0x002BA408.
typedef struct VT { short d; short pad; void *pfn; } VT;
typedef struct A { VT *vt; } A;
typedef struct E { unsigned int key; int k; int v; struct E *next; } E;
typedef struct H { int c; E **ap; int count; A *pa; } H;
void *memset(void *, int, int);

void func_002BA408(H *h, int n)
{
    register E *list asm("s1") = 0; /* pin: scheduling tie list=0 vs i=0 (as in Sly 2) */
    E *e, *next;
    int i;
    for (i = 0; i < h->c; i++) {
        e = h->ap[i];
        if (e) {
            while (e->next)
                e = e->next;
            e->next = list;
            list = h->ap[i];
        }
    }
    h->c = n;
    h->ap = ((E **(*)(void *, void *, int, int))h->pa->vt[3].pfn)((char *)h->pa + h->pa->vt[3].d, h->ap, n * 4, 3);
    memset(h->ap, 0, h->c * 4);
    for (e = list; e; e = next) {
        unsigned int j;
        next = e->next;
        j = e->key % h->c;
        e->next = h->ap[j];
        h->ap[j] = e;
    }
}
