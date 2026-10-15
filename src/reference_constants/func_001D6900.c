// Reference algorithm: src/hand/func_001B1B18.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { int a; int b; int c; };
struct P { char pad[0x15C]; struct E ae[1]; };
int func_001D68F8(int n);
void func_001D6900(struct P *p, int n, int a, int c)
{
    if (func_001D68F8(n) && n != 2 && n != 5) {
        struct E *pe = &p->ae[n];
        pe->a = a;
        if (c != -1)
            pe->c = c;
    }
}
