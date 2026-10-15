// Sly 2 reference: src/hand/func_00131CD8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct VTE {
    short d;
    short pad;
    void (*pfn)();
};
struct X {
    char pad[0x88];
    int f88;
    int f8c;
    char pad2[0x9a - 0x90];
    short f9a;
};
struct C {
    struct VTE *vt;
};
struct S {
    int f0;
    void *f4;
    struct X *px;
    int pad[4];
    struct C *pc;
    int f20;
    int f24;
};
void func_0028F068(void *, struct X *, int);
void func_0028B188(void *, struct X *);
void func_00138E38(struct S *p) {
    if (p->pc) {
        struct C *pc;
        p->px->f88 = p->f24 + 0x1c;
        p->px->f8c = p->f24 + 0x40;
        pc = p->pc;
        ((void (*)(void *, struct X *))pc->vt[2].pfn)((char *)pc + pc->vt[2].d, p->px);
    }
    else {
        p->px->f9a = 0;
        func_0028F068(p->f4, p->px, 0);
        func_0028B188(p->f4, p->px);
    }
}
