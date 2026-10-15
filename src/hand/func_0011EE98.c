// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef struct LM { float gMin; float gMax; } LM;
float func_0011E3B8(float rad);
float GLimitAbs__Fff(float g, float gLimit);

float func_0011EE98(LM *plm, float rad)
{
    float radMid = (plm->gMax + plm->gMin) * 0.5f;
    float radHalf = (plm->gMax - plm->gMin) * 0.5f;
    return func_0011E3B8(radMid + GLimitAbs__Fff(func_0011E3B8(rad - radMid), radHalf));
}
