// Sly 2 reference: src/hand/func_0012CF88.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef struct T { int a; int b; int c; int d; int e; int f; int g; char ab[1]; } T;
typedef struct G { int pad[3]; unsigned int cb; } G;
extern G D_004799AC;
void func_001D2898(void *dst, void *src, unsigned int cb);
void func_0012F378(T *t, T *src, int b, int c)
{
    t->a = src->a;
    t->d = src->d;
    t->f = src->f;
    t->b = b;
    t->c = c;
    func_001D2898(t->ab, src->ab, D_004799AC.cb - 0x1C);
}
