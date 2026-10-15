// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
int func_00240DD8(int x)
{
    int i; int m;
    for (i = 0, m = 1; i < 26; i++, m <<= 1) if (x & m) break;
    return i;
}
