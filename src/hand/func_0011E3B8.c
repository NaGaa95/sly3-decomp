// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
float func_0011EDB8(float gDividend, float gDivisor);

float func_0011E3B8(float rad)
{
    if (rad < -3.14159265359f || 3.14159265359f < rad) {
        float modpos = func_0011EDB8(rad + 3.14159265359f, 2 * 3.14159265359f);
        rad = modpos - 3.14159265359f;
    }
    return rad;
}
