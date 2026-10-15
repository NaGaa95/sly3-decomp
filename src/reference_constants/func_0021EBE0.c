// Reference algorithm: src/hand/func_001DA808.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern struct CLOCK { float a[16]; } D_0036BB9C;
struct S { char p0[0x44]; float g34; };
void func_0021DD20(struct S *p);
void func_0021ED28(struct S *p, int a, int b);
void func_0021EBE0(struct S *p) {
    func_0021DD20(p);
    if (p->g34 <= D_0036BB9C.a[15]) func_0021ED28(p, -1, -1);
}
