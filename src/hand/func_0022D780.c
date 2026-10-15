// Deserialize collection modes and count, allocate and read identifier and quadword arrays, read the optional paired arrays, and initialize the completed resource.
// Reference algorithm: src/hand/func_001E5DF8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct MSG { int cb; int nKind; };
struct P {
    char pad[0xD0];
    int fE0;
    int nE4;
    int c;
    int *aE;
    float *aF0;
    qword *aF4;
    char pad2[0x140 - 0xF8];
    qword *a140;
    qword *a144;
};
void func_00290438(struct P *, void *);
int func_00119128(void *);
int func_00119048(void *);
void *func_001D2470(struct MSG *);
void func_00118DA0(void *, int, void *);
void func_001192D8(void *, qword *);
void func_001519C8(struct P *, void *);
void func_0022DB08(struct P *);
void func_0022D780(struct P *p, void *pbis)
{
    struct MSG msg;
    int i;
    func_00290438(p, pbis);
    p->fE0 = func_00119128(pbis);
    p->nE4 = func_00119128(pbis);
    p->c = func_00119048(pbis);
    msg.cb = p->c * 4;
    msg.nKind = 0x10;
    p->aE = func_001D2470(&msg);
    msg.cb = p->c * 4;
    msg.nKind = 0x10;
    p->aF0 = func_001D2470(&msg);
    msg.cb = p->c * 16;
    msg.nKind = 0x10;
    p->aF4 = func_001D2470(&msg);
    func_00118DA0(pbis, p->c * 4, p->aE);
    for (i = 0; i < p->c; i++)
        func_001192D8(pbis, &p->aF4[i]);
    if (p->fE0) {
        msg.cb = p->c * 16;
        msg.nKind = 0x10;
        p->a140 = func_001D2470(&msg);
        msg.cb = p->c * 16;
        msg.nKind = 0x10;
        p->a144 = func_001D2470(&msg);
        for (i = 0; i < p->c; i++)
            func_001192D8(pbis, &p->a140[i]);
        for (i = 0; i < p->c; i++)
            func_001192D8(pbis, &p->a144[i]);
    }
    func_001519C8(p, pbis);
    func_0022DB08(p);
}
