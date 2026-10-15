// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
float fmodf(float x, float y);

float func_0011EDB8(float gDividend, float gDivisor)
{
    float result = fmodf(gDividend, gDivisor);
    if (result < 0.0f) {
        result += gDivisor;
    }
    return result;
}
