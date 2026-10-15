// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
int func_0011E8B8(void);

int func_0011E8F0(int nLow, int nHi)
{
    int nRand = func_0011E8B8();
    int nBase = nLow - 1;
    return nLow + nRand % (nHi - nBase);
}
