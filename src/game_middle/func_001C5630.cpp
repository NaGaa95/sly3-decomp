// Fit y = pru * x + pdu through two points (Sly 2 FitLinearFunction).
// SLY3_CFLAGS: -Os -G0 -ffast-math -fno-exceptions
// SLY3_ASFIX: engine-divfix1
extern "C" int func_0011E9F0(float a, float b, float eps);
extern "C" void func_001C5630(float x0, float y0, float x1, float y1, float *pdu, float *pru)
{
    if (func_0011E9F0(x0, x1, 0.0001f)) {
        *pru = 0.0f;
        *pdu = y0;
        return;
    }
    float a = (y1 - y0) / (x1 - x0);
    *pru = a;
    *pdu = y0 - a * x0;
}
