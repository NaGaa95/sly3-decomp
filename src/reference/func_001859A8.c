// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
int func_00185980(int i);
int func_001859A8(int c, int *ai)
{
    int grf = 0;
    int i;
    for (i = 0; i < c; i++)
        grf |= func_00185980(ai[i]);
    return grf;
}
