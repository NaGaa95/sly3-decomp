// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: engine-divfix1
/* RGB -> HSV (h in degrees, -1 when s == 0) */
typedef struct VECTOR { float x, y, z; } VECTOR;
static __inline__ float GClamp(float g, float lo, float hi)
{
    if (g < lo) return lo;
    if (g > hi) return hi;
    return g;
}
void func_0011F2E8(VECTOR *prgb, VECTOR *phsv)
{
    float r, g, b, max, min, delta, s, h;
    r = GClamp(prgb->x, 0.0f, 1.0f);
    g = GClamp(prgb->y, 0.0f, 1.0f);
    b = GClamp(prgb->z, 0.0f, 1.0f);
    max = (r > g && r > b) ? r : (g > b ? g : b);
    min = (r < g && r < b) ? r : (g < b ? g : b);
    delta = max - min;
    s = (max != 0.0f) ? delta / max : 0.0f;
    if (s == 0.0f)
        h = -1.0f;
    else {
        if (r == max)
            h = (g - b) / delta;
        else if (g == max)
            h = 2.0f + (b - r) / delta;
        else if (b == max)
            h = 4.0f + (r - g) / delta;
        h *= 60.0f;
        if (h < 0.0f)
            h += 360.0f;
    }
    phsv->x = h;
    phsv->y = s;
    phsv->z = max;
}
