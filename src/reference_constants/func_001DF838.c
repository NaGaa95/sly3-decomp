// Reference algorithm: src/hand/func_001B7050.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct T { char pad[0x190]; int n; };
struct S { char pad[0x153C]; int f; struct T *pt; char pad2[0x1588 - 0x1544]; int g; };
void func_001DE690(struct S *p, int n);
void func_0024E920(struct S *p, int n);
void func_001DF838(struct S *p, struct T *pt)
{
    if (p->f) {
        p->pt = pt;
        p->g = 1;
        func_001DE690(p, 4);
        func_0024E920(p, p->pt->n);
    }
}
