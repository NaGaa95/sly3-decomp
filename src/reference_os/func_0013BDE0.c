// Sly 2 reference: src/hand/func_001334A8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct E { int id; int cref; struct E *pnext; };
struct S { int pad[2]; struct E *pfirst; };
extern char D_004798D0[];
void func_0011E1F0(void *, void *);
void func_0013BDE0(struct S *p) {
    struct E *pe = p->pfirst;
    while (pe) { struct E *pNext = pe->pnext; func_0011E1F0(D_004798D0, pe); pe = pNext; }
    p->pfirst = 0;
}
