// Sly 2 reference: src/hand/func_0012D890.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef struct VT { short d; short pad; void (*fn)(void *); } VT;
typedef struct O { int pad[6]; VT *vt; } O;
typedef struct T { int pad[7]; O *q; } T;
void func_0012FCF0(T *t)
{
    O *p = t->q;
    if (p) {
        p->vt[2].fn((char *)p + p->vt[2].d);
        t->q = 0;
    }
}
