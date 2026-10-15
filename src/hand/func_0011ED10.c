// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef unsigned int uint;

float func_0011ED10(float g)
{
    uint u = *(uint *)&g;
    int exp = ((u >> 23) & 0xFF) - 0x7F;
    if (exp < 0) {
        return 0.0f;
    }
    if (exp < 23) {
        uint mask = (1UL << (23 - exp)) - 1;
        uint frac = u & 0x7FFFFF;
        if ((frac & mask) == mask) {
            *(uint *)&g = (u & 0xFF800000) | (frac & ~mask & 0x7FFFFF);
            g += 1.0f;
        } else {
            *(uint *)&g = (u & 0xFF800000) | (frac & ~mask & 0x7FFFFF);
        }
    }
    return g;
}
