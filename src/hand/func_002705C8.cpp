// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
extern "C" double func_002A3770(double);
extern "C" int func_002705C8(double g)
{
    int exp;
    if (g > 0.0) {
        double l = func_002A3770(g);
        exp = (int)l;
        if (l < 0.0 && l != (double)exp)
            exp--;
    } else {
        exp = 0;
    }
    return exp;
}
