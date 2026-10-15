// Reference algorithm: src/hand/func_0013C2D8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct K { int a; int b; };
extern struct K D_003202F0;
extern char D_00475480[];
struct E { int f0; int f4; int f8; char pad[0x34]; };
struct S { char pad[0x164]; int st; };
void func_0023E110(struct S *, struct E *, int);
int func_0013B500(int, int);
void func_0015DCD0(void *, void *, struct K, int);
void func_0014DA08(struct S *p, struct E *ae, int i) {
    func_0023E110(p, ae, i);
    if (p->st == 5) { struct E *pe = &ae[1 - i]; if (!func_0013B500(pe->f8, 0x33)) func_0015DCD0(D_00475480, p, D_003202F0, 0); }
}
