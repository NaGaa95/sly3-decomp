// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Sly2 reciprocal-fit algorithm, canonical Sly3 symbols and verified float/output inputs.
extern "C" int func_0011E9F0(float a,float b,float epsilon);
extern "C" void func_001C56D0(float x0, float y0, float x1, float y1, float *pdu, float *pru)
{
    float gEpsilon = 0.0001f;
    if (func_0011E9F0(x0, x1, gEpsilon) || __builtin_fabsf(x0) < gEpsilon || __builtin_fabsf(x1) < gEpsilon)
    {
        *pru = 0.0f;
        *pdu = y0;
        return;
    }

    float deltaX = x0 - x1;
    float deltaY = y1 - y0;

    float r = ((x0 * x1) * deltaY) / deltaX;
    float d = y0 - (r / x0);

    *pru = r;
    *pdu = d;
}
