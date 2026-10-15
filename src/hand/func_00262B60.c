// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
void func_00262280(void *p, int k);
void func_00262450(void *p, int k);
void func_00262B60(void *p, int k, int *pk)
{
    if (k == *pk)
        return;
    if (*pk != -1)
        func_00262280(p, *pk);
    *pk = k;
    if (k != -1)
        func_00262450(p, k);
}
