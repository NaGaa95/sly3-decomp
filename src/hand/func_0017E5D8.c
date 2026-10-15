// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
int func_0017E208(void *a, int b, int c, int d, int f, int *pn);
int func_0017E5D8(void *a, int b, int c, int d)
{
    int n;
    if (!func_0017E208(a, b | 0x200, c, d, 1, &n))
        return 0;
    return n;
}
