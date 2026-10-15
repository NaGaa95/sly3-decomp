// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct E { int a; int b; int c; int d; };
void func_00254BB8(struct E *pe, void *p);
void func_00253690(void *p, int mask, int b, int d, struct E *pe)
{
    int i;
    int bit = 1;
    for (i = 25; i >= 0; i--) {
        if (mask & bit) {
            func_00254BB8(pe, p);
            pe->b = b;
            pe->d = d;
        }
        bit <<= 1;
        pe++;
    }
}
