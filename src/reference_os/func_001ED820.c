// Sly 2 reference: src/hand/func_001C0F30.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef struct VECTOR { float x, y, z, w; } __attribute__((aligned(16))) VECTOR;
struct E { VECTOR *pv; short a; short b; };
struct S { int c0; struct E *ae; int c8; VECTOR *av; int c10; int *a14; void *x18; };
struct A { int cb; int align; };
int func_001190A8(void *pbis);
int func_00119048(void *pbis);
void func_00119398(void *pbis, VECTOR *pv);
int func_001191E0(void *pbis);
void *func_001D2470(struct A *pa);
void *func_001D2538(struct A *pa);
void func_001ED820(struct S *p, int c, void *pbis)
{
    struct A a;
    int i, j;
    p->c0 = c;
    p->c8 = func_001190A8(pbis);
    p->c10 = func_001190A8(pbis);
    a.cb = p->c0 * 8;
    a.align = 0x10;
    p->ae = func_001D2470(&a);
    a.cb = p->c8 * 16;
    a.align = 0x10;
    p->av = func_001D2470(&a);
    a.cb = p->c10 * 4;
    a.align = 0x10;
    p->x18 = func_001D2538(&a);
    a.cb = p->c10 * 4;
    a.align = 0x10;
    p->a14 = func_001D2470(&a);
    for (i = 0; i < p->c0; i++) {
        struct E *pe = &p->ae[i];
        pe->pv = &p->av[func_00119048(pbis)];
        pe->a = func_00119048(pbis);
        pe->b = func_00119048(pbis);
    }
    for (j = 0; j < p->c8; j++)
        func_00119398(pbis, &p->av[j]);
    for (j = 0; j < p->c10; j++)
        p->a14[j] = func_001191E0(pbis);
}
