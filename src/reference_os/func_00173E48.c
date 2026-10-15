// Sly 2 reference: src/hand/func_00156BE0.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a[3]; struct VTE *vt; };
void func_001739A8(struct O *o);
void func_00173778(void *x, qword q, int c, struct O **ppo);
void func_00173E48(void *x, qword q, int c, struct O **ppo)
{
    if (*ppo) {
        struct O *o;
        struct VTE *e;
        func_001739A8(*ppo);
        o = *ppo;
        e = &o->vt[2];
        e->pfn((char *)o + e->d);
        *ppo = 0;
    }
    if (x) {
        struct O *o;
        struct VTE *e;
        func_00173778(x, q, c, ppo);
        o = *ppo;
        e = &o->vt[1];
        e->pfn((char *)o + e->d);
    }
}
