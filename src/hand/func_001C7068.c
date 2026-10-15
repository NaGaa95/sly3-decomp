// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
struct E { int k; int a[6]; };
struct L { unsigned int c; struct E ae[16]; };
extern struct E D_00370AD0;
void func_00292034(void *, int, int);
struct E *func_001C7068(struct L *pl, int k)
{
    struct E *pe;
    if (pl->c >= 16)
        return &D_00370AD0;
    pe = &pl->ae[pl->c++];
    func_00292034(pe, 0, sizeof(struct E));
    pe->k = k;
    return pe;
}
