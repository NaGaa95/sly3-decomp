// Reference algorithm: src/hand/func_001DB7A8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00363DE0[];
struct S { int a, b, c; void *vt; char pad[0x20]; int n20; };
struct S *func_0021EB00(struct S *p);
void func_0021FE08(struct S *p);
struct S *func_0021FD90(struct S *p) {
    func_0021EB00(p);
    p->vt = D_00363DE0;
    p->n20 = 0x429;
    func_0021FE08(p);
    return p;
}
