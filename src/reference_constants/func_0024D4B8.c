// Reference algorithm: src/hand/func_00203568.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0xE4]; int a; int b; int c; char pad2[0x10]; int d; };
void func_0028FD70(struct S *p);
void func_0024D4B8(struct S *p) { func_0028FD70(p);
p->a = -1; //P
p->d = -1; //P
p->c = -1; //P
p->b = -2; //P
}
