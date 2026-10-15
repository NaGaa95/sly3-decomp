// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef unsigned int uint;
extern "C" uint func_00196A70(uint value)
{
    uint log2 = 0;
    uint bit = 1;
    while (bit < value && log2 < 31)
    {
        bit <<= 1;
        log2++;
    }
    return log2;
}
