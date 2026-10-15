// Sly 2 reference: src/hand/func_0012D8D8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef struct VT { short d; short pad; void (*fn)(void *); } VT;
typedef struct O { int pad[6]; VT *vt; } O;
typedef struct T { int pad; void *a; void *b; int pad2; O *p; int pad3[2]; O *q; } T;
void func_0028B1B0(void *a, void *b);
void func_0012FD38(T *t)
{
    O *p;
    if (t->q != t->p) {
        func_0028B1B0(t->a, t->b);
        p = t->q;
        if (p)
            p->vt[2].fn((char *)p + p->vt[2].d);
        p = t->p;
        t->q = p;
        if (p)
            p->vt[1].fn((char *)p + p->vt[1].d);
    }
}
