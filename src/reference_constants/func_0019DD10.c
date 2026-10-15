// Reference algorithm: src/hand/func_001816C0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { int a; int b; int c; int d; };
struct S { char pad[0x250]; struct E ae[6]; };
void func_0019DD10(struct S *p, unsigned int i, int a, int d)
{
    if (i < 6) {
        p->ae[i].a = a;
        p->ae[i].d = d;
    }
}
