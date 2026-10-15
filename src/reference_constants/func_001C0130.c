// Reference algorithm: src/hand/func_0019F0A8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { int a, b, c; struct VTE *vt; };
struct G;
extern struct G D_00475480;
int func_0017E208(struct G *, int, int, int, int, struct O **);
void func_001C0130(void) {
    struct O *ap[16];
    int c, i;
    c = func_0017E208(&D_00475480, 5, 0x33, 0, 16, ap);
    for (i = 0; i < c; i++) { struct O *o = ap[i]; struct VTE *e = &o->vt[118]; e->pfn((char *)o + e->d); }
}
