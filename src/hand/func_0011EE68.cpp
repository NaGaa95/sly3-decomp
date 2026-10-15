// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct LM { float gMin; float gMax; };

extern "C" float func_0011EE68(LM *plm, float g)
{
    if (g < plm->gMin) {
        return plm->gMin;
    }
    if (g > plm->gMax) {
        return plm->gMax;
    }
    return g;
}
