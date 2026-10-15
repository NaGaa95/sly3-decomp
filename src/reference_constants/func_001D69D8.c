// Reference algorithm: src/hand/func_001B1BF0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { int a; int b; int c; };
struct S { char pad[0x15C]; struct E ae[6]; };
int func_001D6980(struct S *p, int a);
void func_001D69D8(struct S *p)
{
    int i;
    struct E *pe;
    for (i = 0; i < 6; i++) {
        pe = &p->ae[i];
        if (pe->a != -1) {
            pe->b = func_001D6980(p, pe->a);
            pe->a = -1;
        }
    }
}
