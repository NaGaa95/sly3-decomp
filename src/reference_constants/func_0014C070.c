// Reference algorithm: src/hand/func_0013AAA0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct K { int a; int b; };
struct S { char pad[0x1DC]; int f1f4; int f1f8; int f1fc; };
void func_0023C580(struct S *);
int func_001D2470(struct K *);
void func_0014C070(struct S *p) {
    func_0023C580(p);
    if (p->f1f4) { struct K k; k.a = 0xc0; k.b = 0x10; p->f1fc = func_001D2470(&k); }
}
