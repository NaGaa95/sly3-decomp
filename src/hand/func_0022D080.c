// Dispatch the active state to its embedded controller, fall back to the stored result when needed, and update the owner with the result and output count.
// Reference algorithm: src/hand/func_00135D80.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x298]; int f268; char pad1[0x320 - 0x29C]; int f2c0; char pad2[0x500 - 0x324]; int f4c0; char pad3[0xE40 - 0x504]; int fdf0; char pad4[0x1470 - 0xE44]; int st; };
int func_001B5C78(void *, int *);
int func_001BD718(void *, int *);
int func_001C4088(void *, int *);
void func_0024DF48(struct S *, int, int);
void func_0022D080(struct S *p) {
    int n = 0;
    int r;
    switch (p->st) {
    case 4: r = func_001B5C78(&p->f4c0, &n); break;
    case 5: r = func_001C4088(&p->fdf0, &n); break;
    case 3: r = func_001BD718(&p->f2c0, &n); break;
    default: r = 0; break;
    }
    if (!r) r = p->f268;
    func_0024DF48(p, r, n);
}
