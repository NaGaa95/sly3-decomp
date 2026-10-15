// Sly 2 reference: src/hand/func_00207F50.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct E { int a; int b; int c; int d; };
void func_00254BB8(struct E *pe, void *p);
void func_00254C00(struct E *pe, void *p);
void func_00253728(void *p, int mask, int b, int d, struct E *pe)
{
    int i;
    int bit = 1;
    for (i = 25; i >= 0; i--) {
        if (mask & bit) {
            func_00254BB8(pe, p);
            pe->b = b;
            pe->d = d;
            func_00254C00(pe, p);
        }
        bit <<= 1;
        pe++;
    }
}
