// Reference algorithm: src/hand/func_00131A90.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct X {
    char pad[0x98];
    short f98;
    char pad2[0xe];
    float fa8;
};
struct N {
    int f0;
    void *f4;
    struct X *px;
    char pad[0x1c];
    struct N *pnext;
};
struct S {
    char pad[0x34];
    struct N *pfirst;
};
int func_0012F2D0(struct N *);
void func_0028F068(void *, struct X *, int);
void func_00138BF8(struct S *p, float g) {
    struct N *pn;
    for (pn = p->pfirst; pn; pn = pn->pnext) {
        if (func_0012F2D0(pn) && pn->px->f98 == 8) {
            func_0028F068(pn->f4, pn->px, 10);
            pn->px->fa8 = g;
        }
    }
}
