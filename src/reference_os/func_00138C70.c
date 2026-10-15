// Sly 2 reference: src/hand/func_00131B10.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct N { int f0; int pad[2]; int fc; struct N *pnext; int pad2[4]; int f24; };
struct S { char pad[0x90]; struct N *pn; };
void func_0028EE98(int, struct S *);
void func_00138C70(int id, int a, struct S *p) {
    struct N *pn = p->pn;
    for (;;) {
        if (!pn) return;
        if (pn->f0 == 0 && pn->f24 == id) { pn->fc = -1; func_0028EE98(a, p); return; }
        pn = pn->pnext;
    }
}
