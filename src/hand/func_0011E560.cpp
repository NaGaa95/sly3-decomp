// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
extern "C" float func_0011E560(float g, float gLimit)
{
    if (g > gLimit) {
        g = gLimit;
    } else if (g < -gLimit) {
        g = -gLimit;
    }
    return g;
}
