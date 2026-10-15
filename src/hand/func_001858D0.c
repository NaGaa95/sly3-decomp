// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct E { int a; int b; };
int func_001858D0(int x, struct E *ae, int cMax, int *pc, int a, int b)
{
    struct E *pe;
    if (*pc < cMax) {
        pe = &ae[(*pc)++];
        pe->a = a;
        pe->b = b;
        return 1;
    }
    return 0;
}
